/*
Autor: Florian Mayer
Datum: 17.Sept.2013
Zweck: Operations on string tables
*/

#include <stdio.h>
#include <stdlib.h>
#include "clibf.h"


/*concatenates the arrays dest and src. The result is reallocated in dest which is also
the return value*/
char **clibf_table_cat(char **dest, char **src, int dest_len, int src_len, int size){
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
char **clibf_heap_table(char **table, int len){
	char **result = malloc(len * sizeof(char));
	int i; 
	for(i=0; i< len; i++)
		result[i] = table[i]; 
	return result;
}

/*The table has to lay on the heap!*/
char **clibf_table_add(char **table, char *add, int table_len){
	table = (char **) realloc(table, (table_len + 1) * sizeof(char));
	table[table_len] = add;
	return table;	
}

char **clibf_create_table(int len){
	char **result = (char **) malloc(len*sizeof(char));
	return result;
}
