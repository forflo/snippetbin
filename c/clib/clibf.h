/*********************
 dyn strings
*********************/

#define DYN_INIT_SIZE 100
#define DYN_REALLOC_SIZE 1000

struct dyn_string {
	int chars;
	int space;
	char *data;
};

typedef struct dyn_string dyn_string_t;

/* returns a structure of type dyn_string with preallocated memory 
	for 99 chars */
struct dyn_string *ds_get();
struct dyn_string *ds_get_string(char *str);
void ds_append_string(struct dyn_string *string, char *source);
void ds_append_char(struct dyn_string *string, char source);
void ds_remove_trailing_char(struct dyn_string *string, char c);
void ds_remove_trailing_whitespaces(struct dyn_string *string);
/* 	adapts the memory to the amount of chars in the dyn_string 
	returns: 0 if success and 1 if failure */
int ds_adapt_string(struct dyn_string *string); 
void ds_free(struct dyn_string *string);

/* arr_utils.c */
/*contains various functions for string tables*/

char **clibf_table_cat(char **dest, char **src, 
						int dest_len, int src_len, int size);
char **clibf_heap_table(char **table, int len);
char **clibf_table_add(char **table, char *add, int table_len);
char **clibf_create_table(int len);
