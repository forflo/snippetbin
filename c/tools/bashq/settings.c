#include <getopt.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include "def.h"


static struct settings *args = NULL;
static int ret_code = 0;

/* make capsulation of args complete */
char o_create(){ return args->create; }

char o_recv(){ return args->recv;	}

char o_send(){ return args->send;	}

char o_file(){ return args->file_input; }

char o_version(){ return args->version;	}

char o_help(){ return args->help; }

char o_dest(){ return args->dest; }

int o_len(){ return args->len; }

long o_type(){ return args->type; }

int o_key(){ return args->key; }

int o_perm(){ return args->perm; }

int parse_args(int argc, char **argv){
	/* We alread have an instance of struct settings! */
	if (args != NULL){
		ret_code = SET_RC_EAGAIN;
		return -1;
	}

	int c, op_i, i, j=0, r=0;
	args = (struct settings *) malloc(sizeof(struct settings));
	if(args == NULL){
		ret_code = SET_RC_MEMERR;
		return -1;
	}

	struct settings set = {FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, 0, 0L, 0, 0};
	static struct option opts[] = {
		{"create", no_argument, 0, 'c'},
		{"receive", no_argument, 0, 'r'},
		{"send", no_argument, 0, 's'},
		{"file-input", no_argument, 0, 'f'},
		{"version", no_argument, 0, 'v'},
		{"help", no_argument, 0, 'h'},
		{"destroy", no_argument, 0, 'd'},
		{"length", no_argument, 0, 'l'},
		{"type", no_argument, 0, 't'},
		{"key", no_argument, 0, 'k'},
		{"permission", no_argument, 0, 'p'}
	};
	memcpy(args, &set, sizeof(struct settings));	

	while((c = getopt_long(argc, argv, OPTSTRING, opts, &op_i)) != -1){
		switch(c){
			case 'c': args->create = TRUE; break;
			case 'r': args->recv = TRUE; break;
			case 's': args->send = TRUE; break;
			case 'f': args->file_input = TRUE; break;
			case 'v': args->version = TRUE; break;
			case 'h': args->help = TRUE; break;
			case 'd': args->dest = TRUE; break;
			case 'l': args->len = atol(optarg); break;
			case 't': args->type = atoi(optarg); break;
			case 'k': args->key = atoi(optarg); break;
			case 'p': 
				/* Converts the string representation of the permissioncode 
				   into binary */
				args->perm = 0;
				for (i=strlen(optarg)-1; i>=0; i--){
					if(optarg[i] < 48 || optarg[i] > 57){
						ret_code = SET_RC_PERMPARSE;
						return -1;
					}
					r += pow(8, j++) * (optarg[i]-48);
				}
				j=0;
				do {
					i = r%2;
					args->perm += pow(2, j++) * i;
				} while(r/=2);
				break;
			default : ret_code = SET_RC_ARGERR; return -1; break;
		}
	}

	return 0;
}
