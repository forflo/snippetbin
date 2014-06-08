#define OPTSTRING "hvfcdp:l:k:gs"
#define FALSE 0
#define TRUE 1
#define MAX_READ_BUF 1000
#define STD_PERM 0600

struct settings {
	char create;
	char help;
	char version;
	char destroy;
	char get;
	char set;
	int size;
	int key;
	char file_input;
	char *content;
	int content_bytes;
	int permissions;
};

void usage();
void version();
int init(struct settings *args);
int dest(int shmid);
struct settings *parse_arguments(int argc, char **argv);
int get(struct settings *args, int shmid);
int set(struct settings *args, int shmid);
char *read_buffered(int chunk_size, int fd, int *bytes_read);
void write_buffered(int chunk_size, int fd, char* buffer, int n);
