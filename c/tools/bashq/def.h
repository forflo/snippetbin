#define OPTSTRING "crsfvhdl:t:k:p:"
#define MSG_USAGE "bashq ..."

#define SET_RC_EAGAIN 10
#define SET_RC_MEMERR 11
#define SET_RC_ARGERR 12
#define SET_RC_PERMPARSE 13

#define TRUE 1
#define FALSE 0

struct settings {
	char create;
	char recv;
	char send;
	char file_input;
	char version;
	char help;
	char dest;
	int len;
	long type;
	int key;
	int perm;
};

int parse_args(int argc, char **argv);

void write_buffered(int c, int fd, char *b, int to);
char *read_buffered(int c, int fc, *b);

char o_create();
char o_recv(); 
char o_send();
char o_file();
char o_version();
char o_help();
char o_dest();
int o_len();
long o_type();
int o_key();
int o_perm();
