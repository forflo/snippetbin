#include <stdio.h>
#include "call.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <getopt.h>
#include <openssl/md5.h>
#include <sqlite3.h>

/*funktion definitions*/
int parse_args(int argc, char **argv);
char *buffer_fd(int *count, int fd);
void print_usage(void);
char *get_tempfile(void);

/*string table functions*/
char **table_cat(char **dest, char **src, int dest_len, int src_len, int size);
char **heap_table(char **table, int len);
char **table_add(char **table, char *add, int table_len);
char **create_table(int len);

/*string tokenizer*/
char *str_tok(const char *string, const char *delimiters);

const char *path_gcc = "/usr/bin/gcc";

int mode;
char *prog_name;
char *compiler_flags;
char *code;
char *type;
int read_stdin = 0;

/*sqlite variables*/
sqlite3 *db;
char *sql_error;
static int callback(void *NotUsed, int argc, char **argv, char **col_name){}

int main(int argc, char **argv, char **envp){
	parse_args(argc, argv);
	
//	printf("t: %s, f: %s, s: %d\n", type, compiler_flags, read_stdin);
//	printf("code: %s\n", code);
}

char *get_tempfile(void){
	
}

int parse_args(int argc, char **argv){
	int c;
	char *optstr = "f:t:s";

	while(1){
		static struct option long_options[] = {
			{"type", required_argument, NULL, 't'}, 
			{"flags", required_argument, NULL, 'f'},
			{"stdin", no_argument, NULL, 's'},
			{0, 0, 0, 0}
		};

		int option_index = 0;
		c = getopt_long_only(argc, argv, optstr, long_options, &option_index);
	
		if(c == -1)
			break;
	
		switch(c){
			case 's':
				//hier wurde -s abgefangen, da das setzen schon mit dem funktionaufruf
				//von getopt_long_only erfolgte
				read_stdin = 1;
			break;
			case 't':
				type = optarg;
			break;
			case 'f':
				compiler_flags = optarg;
			break;
			case '?':
				printf("Ein Fehler beim Parsen der Argumente ist aufgetreten!\n");
				print_usage();
			break;
			default:
				exit(1);
			break;
		}
	}

	//no stdin mode and no code!	
	if (read_stdin == 0 && argc - optind == 1){
		print_usage();	
	//get name and code
	} else if (read_stdin == 1 && argc -optind == 1){
		print_usage();
	} else if (argc -optind == 2) {
		prog_name = argv[optind++];
		code = argv[optind];
	//get name and code in stdin mode
	} else if (read_stdin == 1){
		prog_name = argv[optind++];
		int max = 100;
		int i, p = 0, count = 0, temp = 0;
		char *buffer = (char *)malloc(max*sizeof(char));
		while (1){
			temp = read(STDIN_FILENO, buffer+count, max);
			if(temp == 0) break;
			count += temp;
			buffer = (char*) realloc(buffer, (max+(++p*max))*sizeof(char));
		}
		
		code = (char*) malloc(count*sizeof(char)); //don't forget to free this!
		for (i=0; i<count; i++) code[i] = buffer[i];
		free(buffer);
	} else {
		print_usage();
	}

	return 0;
}

void print_usage(){
	printf("[usage] <program> [ -t <language_type> ] [ --not-persistent ] <code>\n");
	printf("Currently available Languate-types:\n");
	int i;
	for (i=0; i<NUM_LANGS;i++){
		printf("\t%s\n", allowed_langs[i]);
	}
}

//not tested
char *buffer_fd(int *count, int fd){
	int c = 0, t = 0, p = 0, max = 100;
	char *buf = (char *) malloc(max*sizeof(char));
	while(1){
		t = read(fd, buf+c, max);
		c += t;
		if(t == 0) break;	
		buf = (char *) realloc(buf, (max+(++p*max))*sizeof(char));
	}
	buf = (char *)realloc(buf, c * sizeof(char));
	return buf;
}

char *get_hash(const char *str) {
    int n, len = strlen(str);
    MD5_CTX c;
    unsigned char digest[16];
    char *out = (char*)malloc(33);

    MD5_Init(&c);

    while (len > 0) {
        if (len > 512) {
            MD5_Update(&c, str, 512);
        } else {
            MD5_Update(&c, str, len);
        }
        len -= 512;
        str += 512;
    }

    MD5_Final(digest, &c);

    for (n = 0; n < 16; ++n) {
        snprintf(&(out[n*2]), 16*2, "%02x", (unsigned int)digest[n]);
    }

    return out;
}


void compile_c(const char *code, const char *infile, const char *outfile){
	pid_t pid;
	switch(pid = fork()){
		case -1:
			printf("Fehler beim Forken!\n");
			break;
		case 0:
			printf("Starte GCC\n");
			execl(path_gcc, "/usr/bin/gcc", "-o", infile, outfile, NULL);
			printf("Kompiliervorgang konnte nicht abgeschlossen werden!\n");
			break;
		default:
		break;
	}
}

/*sqlite functions*/
int setup_db(char *path){
	char *err;
	int rc = sqlite3_exec(db, "create table bin_bucket (id text not null, bin blob not null, name text not null, code text not null, primary key(id));", NULL, 0, &err);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "Ein SQL-Error ist aufgetreten!\n");
		fprintf(stderr, "Nachricht: %s\n", err);
		return 1;
	} else return 0;
}

int open_db(char *path){
	int rc = sqlite3_open(path, &db);
	if(rc){
		fprintf(stderr, "Fehler beim Öffnen der Datenbank!");
		sqlite3_close(db);
		return 1;
	}
	return 0;
}

int add(const char *name, const char *blob, const char *code){
	
}

int drop(const char *name){

}

char *read_program(const char *name){
	
}

int is_added(char *name){
	char stmt[130] = "select name from bin_bucket where name = '";
	strcat(stmt, name);
	strcat(stmt, "';");
	sqlite3_stmt *comp_st;
	int rc = sqlite3_prepare(db, stmt, -1, &comp_st, NULL);
	if (rc != SQLITE_OK){
		printf("[is_added] SQL_Fehler!\n");
		return 1;
	}
	
	sqlite3_finalize(comp_st);
	if (count_rows(comp_st) == 0) return 0;
	else return 1;
}

int count_rows(sqlite3_stmt *stmt){
        int count=0, rc;
        while ((rc = sqlite3_step(stmt)) != SQLITE_DONE){
                if (rc == SQLITE_ROW) count ++;
                else return -1;
        }
        return count;
}

/*contains various functions for string tables*/

/*concatenates the arrays dest and src. The result is reallocated in dest which is also
the return value*/
char **table_cat(char **dest, char **src, int dest_len, int src_len, int size){
	int i;
	char **result = (char **) malloc((dest_len + src_len) * size);
	if(dest == NULL)
		return NULL;	
	for(i=0; i<dest_len; i++)
		result[i] = dest[i];
	for(i=dest_len; i<src_len; i++)
		result[i] = src[i];
	return result;
}

/*takes an compile-time allocated buffer and copies it into an
runtime allocated one*/
char **heap_table(char **table, int len){
	char **result = malloc(len * sizeof(char));
	int i; 
	for(i=0; i< len; i++)
		result[i] = table[i]; 
	return result;
}

/*The table has to lay on the heap!*/
char **table_add(char **table, char *add, int table_len){
	table = (char **) realloc(table, (table_len + 1) * sizeof(char));
	table[table_len] = add;
	return table;	
}

char **create_table(int len){
	char **result = (char **) malloc(len*sizeof(char));
	return result;
}

/*a string tokenizer*/
char *str_tok(const char *string, const char *delimiters){
	static int pr = 0, sp = 0;
	static int fin = 0;
	int i;
	while(*(string+sp) != '\0'){
		for(i=0; i<strlen(delimiters);i++){
			if(*(string+sp) == *(delimiters+i)){
				char *result = (char *) malloc((sp - pr + 1) * sizeof(char));	
				strncpy(result, string + pr, sp - pr);
				result[sp - pr] = '\0';
				pr = sp++ + 1;
				return result;
			}
		}
		sp++;
	}

	if(fin != 1){
		char *result = (char *) malloc((sp - pr + 1) * sizeof(char));
		strncpy(result, string + pr, sp - pr);
		result[sp - pr] = '\0';
		fin = 1;
		return result;
	} else {
		pr=0, sp=0, fin=0;
		return NULL;
	}
}
