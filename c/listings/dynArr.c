#include <stdio.h>
#include <stdlib.h>

int **get2Dim(int zeile, int spalte){
	int i;
	int **matrix;
	matrix = malloc(zeile * sizeof(int *));
	if (matrix == NULL){
		printf("[get2Dim]: Keine Speicherallokierung mehr möglich \n");
		return NULL;
	}

	for(i = 0; i < zeile; i++){
		*(matrix + i) = malloc(spalte * sizeof(int));
		if(*(matrix + i) == NULL){
			printf("[get2Dim]: Keine Speicherallokierung mehr möglich \n");
			return NULL;
		}
	}
	
	return matrix;
}

int ***get3Dim(int zeile, int spalte, int tiefe){
	int i, j;
	int ***matrix;
	matrix = malloc(zeile * sizeof(int **));
	
	if (matrix == NULL){
		printf("[get3Dim]: Keine Speicherallokierung mehr möglich \n");
		return NULL;
	}
	
	for(i = 0; i < zeile; i++){
		*(matrix + i) = malloc(spalte * sizeof(int *));
		if( *(matrix + i) == NULL){
			printf("[get3Dim]: Keine Speicherallokierung mehr möglich\n");
			return NULL;
		}
	}
	
	for(i = 0; i < zeile; i++){
		for ( j = 0; j < spalte; j++) {
			*(*(matrix + i) + j) = malloc(tiefe * sizeof(int));
			if (*(*(matrix + i) + j) == NULL ){
				printf("[get3Dim]: Keine Speicherallokierung mehr möglich\n");
				return NULL;
			}
		}
	}
	
	return matrix;
}

int free3Dim(int ***matrix, int zeile, int spalte, int tiefe){
	int i, j; 
	for(i = 0; i < zeile; i++)
		for(j = 0; j < spalte; j++)
			free(*(*(matrix + i) + j));

	for(i = 0; i < zeile; i++)
		free(*(matrix + i));

	free(matrix);
}
