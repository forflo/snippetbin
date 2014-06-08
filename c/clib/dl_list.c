/**
Autor: Florian Mayer
Datum: 19.Sept
Zweck: Provides more generic c functions for manipulating
		single linked lists

**/

#include <stdlib.h>
#include <stdio.h>
#include "structs.h"

/*Function definitions!*/
t_list *init_gen_dl();
int add_at_dl(t_list *list, int index, void *content);
int add_dl(t_list *list, void *content);
int prepend_dl(t_list *list, void *content);
int free_list_dl(t_list *list);
int rm_at_dl(t_list *list, int index);
int rm_last_dl(t_list *list, int index);
int rm_content_dl(t_list *list, void *content);

t_list *init_gen_dl(){
	t_list *list = (t_list *) malloc(sizeof(t_list));
	list->len = 0;
	list->start = NULL;
	return list;
}

/*Appends an item on the list
if the list is empty, the first item will be created*/
int add_dl(t_list *list, void *content){
	if(list == NULL) return 1;
	if((list->start) == NULL) {
		t_node *node = (t_node *) malloc(sizeof(t_node));
		node->content = content;
		node->next = NULL;
		list->start = node;
	} else {
		t_node *temp = list->start;
		while(1){
			if((temp->next) != NULL){
				temp = temp->next;
			} else {
				t_node *next = (t_node *) malloc(sizeof(t_node));
				next->content = content;
				next->next = NULL;
				break;
			}
		}
	}
	list->len++;
	return 0;
}

int prepend_dl(t_list *list, void *content){
	add_at_dl(list, 0, content);
}

/*this function adds a item before the index
the function appends a node only if the list is empty*/
int add_at_dl(t_list *list, int index, void *content){
	if(list == NULL || index < 0 || content == NULL) return 1;
	if((list->len) < index) {
		return 1;
	}
	if(list->len == 0 && index == 0) { 
		t_node *node = (t_node *) malloc( sizeof(t_node));
		node->next = NULL;
		node->content = content;
		list->start = node;
	} else {
		int i;
		t_node *temp = list->start;
		for(i=0; i<index; i++){
			temp = temp->next;
		}
		t_node *next = temp->next;
		t_node *new = (t_node *) malloc(sizeof(t_node));
		new->next = next;
		new->content = content;
		temp->next = new;
	}
	return 0;
}

int rm_at_dl(t_list *list, int index){
	if(list == NULL || index < 0) return 1;
	if((list->len) == 0) return 1;

	if(index < 0) return 1;
	else {
		int i; t_node *temp = list->start, *prev = NULL;
		for(i=0; i<index; i++){
			prev = temp;
			temp = temp->next;
		}
		t_node *save = temp->next;
		free(temp);
		prev->next = save;
	}
	return 0;
}

int rm_last_dl(t_list *list, int index){
	if (list == NULL) return 1;
	return rm_at_dl(list, (list->len)-1);
}

int rm_content_dl(t_list *list, void *content){
	if(list == NULL || content == NULL) return 1;
	if(list->len == 0) return 1;
	else {
		t_node *temp = list->start;
		t_node *prev = NULL;
		while(temp->content != content){
			prev = temp;
			temp = temp->next;
		}
		t_node *save = temp->next;
		prev->next = save;
		free(temp);
	}
	return 0;
}

int free_list_dl(t_list *list){
	if(list == NULL) return 1;
	if(list->start == NULL){
		free(list);
	} else {
		t_node *temp = list->start;
		t_node *old;
		while(1){
			if((temp->next) == NULL) { free(temp); break; }
			old = temp;
			temp = temp->next;
			free(old);
		}
	}
	return 0;
}
