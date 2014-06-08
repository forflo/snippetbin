/*author: florian mayer
  date: 08.02.2014
  summary: This tool, called bashm, brings shared memory functionality to the shell. It has
  a very simple CLI described in the function usage(). SHM segments can be created, destroyed, read and
  written through statements such as --get, --destroy, --set or --create. The single segments are referenced
  via the Sys-V IPC key. As a consequence, independent bash processes will be able to use something like
  global variables much more flexible than e.g. fifos and much nicer than temporary files */

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <getopt.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <math.h>
#include "bashm.h"

/* Returncode handling code packaged in macros to reduce redundancy */
#define HANDLE_SHMGET_RC  switch(errno){ \
	case ENOENT: \
		printf("SHM segment with key %d could not be found!\n", args->key);\
		break;\
	case EACCES: \
		printf("SHM segment exists but insufficient permissions!\n"); \
		break; \
	case EEXIST: \
		printf("SHM segment already exists!\n"); \
		break; \
	case EINVAL: \
		printf("SHM segment exists for key %d but with different size\n", args->key); \
		break;\
	case ENOMEM: \
		printf("Not enough memory left!\n"); \
		break;\
	case ENOSPC: \
		printf("Excision of SHM segment limit!\n"); \
		break;\
}\

#define HANDLE_SHMAT_RC switch(errno){ \
	case EACCES:\
		printf("Permission issue!\n"); \
		break;\
	case EINVAL: \
		printf("SHMID %d is not valid!\n", shmid); \
		break;\
	case EMFILE: \
		printf("Number of SHM segment exceedet the system-wide limit!\n"); \
		break;\
	case ENOMEM: \
		printf("There is not enough memory to do that!\n"); \
		break;\
}\

#define HANDLE_SHMCTL_RC switch(errno){ \
	case EACCES: \
		printf("Permission issues!\n"); \
		break; \
	case EFAULT: \
		printf("False parameter to shmctl! This is no common error!\n"); \
		break;\
	case EINVAL: \
		printf("Shmid %d is not valid!\n", shmid); \
		break;\
	case EPERM: \
		printf("Permission issues!\n"); \
		break;\
}\

void version(){
	printf("version..\n");
}

void usage(){
	printf("usage: <prog> [ -c | --create ] \n\
    [ -d | --destroy ] \n\
    [ -g | --get ] \n\
    [ -s | --set ] \n\
    [ -p | --permissions ] \n\
    [ -k | --key <KEY> ] //The key for the Shared Memory segment \n\
    [ -l | --length <size in bytes> ] //Size of the shm. Needs to be specified if -c is set \n\
    [ -f | --file-input ] // bashm takes the stream stdin, and writes that as content \n\
    <string>\n\
\n\
    If --get is used, bashm will read from the shared memory segment untin \n\
    it hits a \\0. This behaviour can changed if an additional -l <num of bytes> is specified \n\
\n\
    If --set is used, bashm will only write the parameter following \"-s\" or \"--set\" into the shm segment\n");

	/* If --get is used withoud any further options, bashm will read until it reaches the
		ASCII null value. If --length <bytes> is specified additionally, only <bytes> bytes are
		read and written to STDOUT */	
}

/* Destroys a shm segment associated with shmid
	Param: shmid = A vailid shared memory segment identifier
	Return: 0 on success. Program exit on failure */
int dest(int shmid){
	if(shmctl(shmid, IPC_RMID, 0) < 0){
		HANDLE_SHMCTL_RC
		return -1;
	}
	printf("Segment with Id %d deleted!\n", shmid);
	return 0;
}

int init(struct settings *args){
	int shmid;
	if((shmid = shmget(args->key, args->size, args->permissions | IPC_CREAT | IPC_EXCL)) < 0){
		HANDLE_SHMGET_RC
	} 
	return shmid;
}

int getid(struct settings *args){
	int shmid;
	if((shmid = shmget(args->key, 0, 0)) < 0){
		HANDLE_SHMGET_RC
	}
	return shmid;
}

/* Reads the contents of a shm segment and writes them to STDOUT
	Param: args = Pointer to a settings object | shmid = a valid shm identifier
	Return: -1 on failure, 0 on success */
int get(struct settings *args, int shmid){
	void *b;
	if((b = shmat(shmid, NULL, SHM_RND)) == (void *) -1){
		HANDLE_SHMAT_RC
		return -1;
	}

	/* Gebe den Puffer auf Stdout aus */	
	if(args->size == 0){
		printf("%s", (char*) b);
	} else {
		write_buffered(MAX_READ_BUF, STDOUT_FILENO, b, args->content_bytes);	
	}
	if(shmdt(b) < 0 ) {
		/* There is only one possible reason for a call fail */
		printf("%p does not point to a mapped shm segment!\n", b);
		return -1;
	}
	return 0;	
}

/* Writes the contents of args->content or STDIN to a shm segment 
	Param: args = Pointer to a settings object | shmid = a valid shm identifier
	Return: -1 on failure, 0 on success */
int set(struct settings *args, int shmid){
	void *b;
	if((b = shmat(shmid, NULL, SHM_RND)) == (void *) -1){
		HANDLE_SHMAT_RC
		return -1;
	}
	memcpy(b, (void *) args->content, args->content_bytes); 
	if(shmdt(b) < 0) {
		printf("%p does not point to a mapped shm segment!\n", b);
		return -1;
	}
	return 0;
}

/* Just debugging ...*/
void show_options(struct settings *args){
	printf("get: %d, set: %d, create: %d, destroy: %d, permissions: %d, size: %d, key: %d, content: %s, file: %d, content länge: %d\n",args->get,
	args->set, args->create,
	args->destroy, args->permissions,
	args->size, args->key,
	args->content, 
	args->file_input,
	args->content_bytes);
}

/* Parses the given arguments. 
	Param: argc = Number of program parameters. argv = Pointer to parameter Table
	Return: initialized and populated pointer to an settings object. NULL if failure */
struct settings *parse_args(int argc, char **argv){
	int c, oi, len;
	int r=0, i, j = 0;
	struct settings *s = (struct settings *) malloc(sizeof(struct settings));
	static struct option long_options[] = {
		{"help", no_argument, 0, 'h'},
		{"version", no_argument, 0, 'v'},
		{"create", no_argument, 0, 'c'},
		{"file-input", no_argument, 0, 'f'},
		{"destroy", no_argument, 0, 'd'},
		{"length", required_argument, 0, 'l'},
		{"key", required_argument, 0, 'k'},
		{"permissions", required_argument, 0, 'p'},
		{"get", no_argument, 0, 'g'},
		{"set", no_argument, 0, 's'}
	};

	/* hand over the failure to caller */
	if(s == NULL){
		return NULL;
	}

	s->get = 0; s->set = 0;
	s->create = 0; s->destroy = 0;
	s->permissions = STD_PERM; s->content = NULL;
	s->key = 0; s->size = 0;
	s->content_bytes = 0;

	/* Abort if not enough parameters have been given */
	if (argc <= 1){
		return NULL;
	}

	while((c = getopt_long(argc, argv, OPTSTRING, long_options, &oi)) != -1){
		switch (c) {
			case 'h': 
				s->help = TRUE; 
				break;
			case 'v': 
				s->version = TRUE; 
				break;
			case 'c': 
				s->create = TRUE; 
				break;
			case 'f': 
				s->file_input = TRUE; 
				break;
			case 'd': 
				s->destroy = TRUE; 
				break;
			case 'l': 
				s->size = atoi(optarg); 
				break;
			case 'k': 
				s->key = atoi(optarg); 
				break;
			case 'p': 
				/* Conversion of the string representation of an octal number into a binary one */
				s->permissions = 0;
				for (i=strlen(optarg)-1; i>=0; i--){
					if(optarg[i] < 48 || optarg[i] > 57){
						printf("Permissions have to be given as octal number\n");
						return NULL;
					}
					r += pow(8, j++) * (optarg[i]-48);
				}
				j=0;
				do {
					i = r%2;
					s->permissions += pow(2, j++) * i;
				} while(r/=2);
				break;
			case 'g': 
				s->get = TRUE; 
				break;
			case 's': 
				s->set = TRUE; 
				break;
			default: 
				return NULL; 
				break;
		}
	}

	/* User wishes input over STDIN*/
	if (s->file_input) {
		s->content = read_buffered(MAX_READ_BUF, STDIN_FILENO, &(s->content_bytes));	
		if(s->content == NULL){
			return NULL;
		}
	/* If optind < argc => There are further parameter. In this case: The String to write */
	} else if (optind < argc) {
		len = strlen(argv[optind]);
		s->content = (char *) malloc(sizeof(char) * (len + 1));
		if(s->content == NULL)
			return NULL;
		s->content_bytes = len + 1;
		strcpy(s->content, argv[optind]);
	} else {
		s->content = (char *) malloc(sizeof(char));
		if(s->content == NULL)
			return NULL;
		s->content_bytes = 1;
		*(s->content) = '\0';
	}
	return s;
}

char *read_buffered(int chunk_size, int fd, int *bytes_read){
	int c = 0, t = 0, p = 0;
	char *buf = (char *) malloc(chunk_size * sizeof(char));	
	if (buf == NULL)
		return buf;
	for(;;){
		if((t = read(fd, buf+c, chunk_size)) == 0) 
			break;
		c += t;
		buf = (char *) realloc(buf, (chunk_size + (chunk_size * ++p)) * sizeof(char));
		if (buf == NULL)
			return buf;
	}
	*bytes_read = c;
	return buf;
}

void write_buffered(int chunk_size, int fd, char* buffer, int to_write){
	int w=0;
	while (to_write){
		if(to_write < chunk_size)
			chunk_size = 1;
		w = write(fd, buffer, chunk_size);
		to_write -= w;
		buffer += w;
	}	
}

int main(int argc, char **argv){
	struct settings *args = parse_args(argc, argv);
	if(args == NULL){
		printf("Error while parsing bashm's arguments!\n");
		exit(1);
	}
	//show_options(args);
	int shmid;

	/* --help or --version should prevent the program from running normally */
	if (args->help){
		usage();
	} else if (args->version){
		version();
	/* if no permission is given, the standard is used, which is 0600 */
	} else if (args->create && args->key && args->size){
		if(init(args) < 0) 
			exit(1); 
	} else if (args->destroy && args->key){
		if(dest(getid(args)) < 0)
			exit(1);
	} else if (args->get && args->key){
		args->content_bytes = args->size;
		if(get(args, getid(args)) < 0)
			exit(1);
	} else if (args->set && args->key){
		/* if no data is provided (neither through args->content nor through STDIN) 
			everything ist fine. Just the ASCII null will be written */
		if(set(args, getid(args)) < 0)
			exit(1);
	} else {
		usage();
	}

	free(args->content);
	free(args);
	return EXIT_SUCCESS;
}
