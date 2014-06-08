typedef struct node t_node;
typedef struct list t_list;

struct list {
	int len;
	t_node *start;
};

struct node {
	void *content;
	t_node *next;
};

/*build an single linked list*/
t_list *init_gen();

/*add something to the end of the list*/
int add(t_list *list, void *content);

/*get something from a index*/
void *get_at(int index, t_list *list, int *fehler);

/*free the whole list*/
int free_list(t_list *list);
