/**
Autor: Florian Mayer
Datum: 19.Sept.2013
Zweck: 	Provides list functions for various trivial 
		types. There are four types listed below:
		- int
		- char
		- double
		- float
		- maybe more the next few days...

		The functions on these list's include the following:
		- add a object
		- remove a object (to be implemented)
		- print the whole list (for debugging purposes)
		- free the whole list

		Useful functions could be:
		- get a cluster of objects from a list
		- push and pop (implementing a stack using a single linked list)
		
**/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

typedef struct float_list t_float_list;
typedef struct float_node t_float_node;

typedef struct double_list t_double_list;
typedef struct double_node t_double_node;

typedef struct int_list t_int_list;
typedef struct int_node t_int_node;

typedef struct char_node t_char_node;
typedef struct char_list t_char_list;

/*char list*/
struct char_list {
	int len;
	struct char_node *start;
};

struct char_node {
	char content;
	struct char_node *next;
};

t_char_list *init_char(){
	t_char_list *result = (t_char_list *) malloc(sizeof(t_char_list));
	result->len = 0;
	result->start = NULL;
	return result;
}

int add_char(t_char_list *list, int var){
	if(list == NULL) return 1;	
	if((list->start) == NULL){
		t_char_node *node = (t_char_node *) malloc(sizeof(t_char_node *));
		node->content=var;
		node->next = NULL;
		list->start = node;
	} else {
		t_char_node *temp = list->start;
		while(1){
			if((temp->next) != NULL){
				temp = temp->next;
			} else {
				t_char_node *next = (t_char_node *) malloc(sizeof(t_char_node *));
				next->content = var;
				next->next = NULL;
				temp->next = next;
				break;
			}
		}
	}
	list->len++;
	return 0;
}

int free_char_list(t_char_list *list){
	if(list == NULL) return 1;
	if(list->start == NULL){
		free(list);
	} else {
		t_char_node *temp = list->start;
		t_char_node *old;
		free(list);
		while(1){
			if((temp->next)==NULL) { free(temp); break; }
			old = temp;
			temp = temp->next;
			free(old);
		}
	}
	return 0;
}

char get_char_at(int index, t_char_list *list, int *fehler){
	if(list == NULL) { *fehler = 1; return 0; }
	if((list->start) == NULL){ *fehler = 1; return 0; }
	if((list->len) <= index) { *fehler = 1; return 0; }
	t_char_node *temp = list->start;
	int i;
	for(i=0; i<index; i++){
		temp = temp-> next;
	}
	*fehler = 0;
	return temp->content;
}

int print_char_list(t_char_list *list){
	int i = 0;
	if(list == NULL) return 1;
	if((list->start) == NULL) return 1;
	else {
		t_char_node *temp = list->start;
		while(1){
			printf("Index: %d - Wert: %c \n", i++, temp->content);
			if((temp->next) == NULL) break;
			temp = temp->next;
		}
	}
}

/*double_list*/
struct double_list {
	int len;
	struct double_node *start;
};

struct double_node {
	double content;
	struct double_node *next;
};

t_double_list *init_double(){
	t_double_list *result = (t_double_list *) malloc(sizeof(t_double_list));
	result->len = 0;
	result->start = NULL;
	return result;
}

int add_double(t_double_list *list, int var){
	if(list == NULL) return 1;	
	if((list->start) == NULL){
		t_double_node *node = (t_double_node *) malloc(sizeof(t_double_node *));
		node->content=var;
		node->next = NULL;
		list->start = node;
	} else {
		t_double_node *temp = list->start;
		while(1){
			if((temp->next) != NULL){
				temp = temp->next;
			} else {
				t_double_node *next = (t_double_node *) malloc(sizeof(t_double_node *));
				next->content = var;
				next->next = NULL;
				temp->next = next;
				break;
			}
		}
	}
	list->len++;
	return 0;
}

int free_double_list(t_double_list *list){
	if(list == NULL) return 1;
	if(list->start == NULL){
		free(list);
	} else {
		t_double_node *temp = list->start;
		t_double_node *old;
		free(list);
		while(1){
			if((temp->next)==NULL) { free(temp); break; }
			old = temp;
			temp = temp->next;
			free(old);
		}
	}
}

double get_double_at(int index, t_double_list *list, int *fehler){
	if(list == NULL) { *fehler = 1; return 0; }
	if((list->start) == NULL){ *fehler = 1; return 0; }
	if((list->len) <= index) { *fehler = 1; return 0; }
	t_double_node *temp = list->start;
	int i;
	for(i=0; i<index; i++){
		temp = temp-> next;
	}
	*fehler = 0;
	return temp->content;
}

int print_double_list(t_double_list *list){
	int i = 0;
	if(list == NULL) return 1;
	if((list->start) == NULL) return 1;
	else {
		t_double_node *temp = list->start;
		while(1){
			printf("Index: %d - Wert: %lf \n", i++, temp->content);
			if((temp->next) == NULL) break;
			temp = temp->next;
		}
	}
}

/*float_list*/
struct float_list {
	int len;
	struct float_node *start;
};

struct float_node {
	float content;
	struct float_node *next;
};

t_float_list *init_float(){
	t_float_list *result = (t_float_list *) malloc(sizeof(t_float_list));
	result->len = 0;
	result->start = NULL;
	return result;
}

int add_float(t_float_list *list, int var){
	if(list == NULL) return 1;	
	if((list->start) == NULL){
		t_float_node *node = (t_float_node *) malloc(sizeof(t_float_node *));
		node->content=var;
		node->next = NULL;
		list->start = node;
	} else {
		t_float_node *temp = list->start;
		while(1){
			if((temp->next) != NULL){
				temp = temp->next;
			} else {
				t_float_node *next = (t_float_node *) malloc(sizeof(t_float_node *));
				next->content = var;
				next->next = NULL;
				temp->next = next;
				break;
			}
		}
	}
	list->len++;
	return 0;
}

int free_float_list(t_float_list *list){
	if(list == NULL) return 1;
	if(list->start == NULL){
		free(list);
	} else {
		t_float_node *temp = list->start;
		t_float_node *old;
		free(list);
		while(1){
			if((temp->next)==NULL) { free(temp); break; }
			old = temp;
			temp = temp->next;
			free(old);
		}
	}
}

float get_float_at(int index, t_float_list *list, int *fehler){
	if(list == NULL) { *fehler = 1; return 0; }
	if((list->start) == NULL){ *fehler = 1; return 0; }
	if((list->len) <= index) { *fehler = 1; return 0; }
	t_float_node *temp = list->start;
	int i;
	for(i=0; i<index; i++){
		temp = temp-> next;
	}
	*fehler = 0;
	return temp->content;
}

int print_float_list(t_float_list *list){
	int i = 0;
	if(list == NULL) return 1;
	if((list->start) == NULL) return 1;
	else {
		t_float_node *temp = list->start;
		while(1){
			printf("Index: %d - Wert: %f \n", i++, temp->content);
			if((temp->next) == NULL) break;
			temp = temp->next;
		}
	}
}
/*int_list*/
struct int_list {
	int len;
	struct int_node *start;
};

struct int_node {
	int content;
	struct int_node *next;
};

t_int_list *init(){
	t_int_list *result = (t_int_list *) malloc(sizeof(t_int_list));
	result->len = 0;
	result->start = NULL;
	return result;
}

int add_int(t_int_list *list, int var){
	if(list == NULL) return 1;	
	if((list->start) == NULL){
		t_int_node *node = (t_int_node *) malloc(sizeof(t_int_node *));
		node->content=var;
		node->next = NULL;
		list->start = node;
	} else {
		t_int_node *temp = list->start;
		while(1){
			if((temp->next) != NULL){
				temp = temp->next;
			} else {
				t_int_node *next = (t_int_node *) malloc(sizeof(t_int_node *));
				next->content = var;
				next->next = NULL;
				temp->next = next;
				break;
			}
		}
	}
	list->len++;
	return 0;
}

int free_int_list(t_int_list *list){
	if(list == NULL) return 1;
	if(list->start == NULL){
		free(list);
	} else {
		t_int_node *temp = list->start;
		t_int_node *old;
		free(list);
		while(1){
			if((temp->next)==NULL) { free(temp); break; }
			old = temp;
			temp = temp->next;
			free(old);
		}
	}
}

int get_int_at(int index, t_int_list *list, int *fehler){
	if(list == NULL) { *fehler = 1; return 0; }
	if((list->start) == NULL){ *fehler = 1; return 0; }
	if((list->len) <= index) { *fehler = 1; return 0; }
	t_int_node *temp = list->start;
	int i;
	for(i=0; i<index; i++){
		temp = temp-> next;
	}
	*fehler = 0;
	return temp->content;
}

int print_int_list(t_int_list *list){
	int i = 0;
	if(list == NULL) return 1;
	if((list->start) == NULL) return 1;
	else {
		t_int_node *temp = list->start;
		while(1){
			printf("Index: %d - Wert: %d \n", i++, temp->content);
			if((temp->next) == NULL) break;
			temp = temp->next;
		}
	}
}


int main(void){
	t_char_list *list = init_char();
	int i;
	for(i=0; i<15; i++){
		printf("Hinzufügen von %d\n", i);
		if(add_char(list, (char) i + 'A')) printf("Fehler beim Hinzufügen");
	}
	printf("Länge der Liste: %d\n", list->len);
	int rc; 
	char result  = get_char_at(15, list, &rc);
	if(rc){
		printf("Fehler beim Abfragen der Liste!\n");
	} else {
		printf("Der Wert an der Stelle %d ist: %c\n", 15, result);
	}
	result  = get_char_at(14, list, &rc);
	if(rc){
		printf("Fehler beim Abfragen der Liste!\n");
	} else {
		printf("Der Wert an der Stelle %d ist: %c\n", 14, result);
	}
	return EXIT_SUCCESS;
}
