#include <stdio.h>
#include <stdlib.h>

int **get_matrix(int zeile, int spalte){
	int i , j;
	int **matrix;
	matrix = malloc(zeile * sizeof(int));
	if( matrix == NULL){
		printf("Kein virtueller RAM mehr vorhanden\n");
		return NULL;
	}
	for(i = 0; i < zeile; i++){
		matrix[i] = calloc (spalte,  sizeof(int));
		if( matrix[i] == NULL) {
			printf("Kein virtueller RAM mehr vorhanden\n");
			return NULL;
		}
	}
	for(i = 0; i < zeile; i++)
		for(j = 0; j < spalte; j++)
			matrix[i][j] = i+j;	

	return matrix;
}

int main(void){
	int i, j, zeile, spalte;
	int **matrix;

	printf("Wie viele Zeilen : ");
	scanf("%d", &zeile);
	printf("Wie viele Spalen : ");
	scanf("%d", &spalte);
	
	matrix = malloc(zeile * sizeof(int));
	if( matrix == NULL)
		return -1;
	for(i = 0; i < zeile; i++){
		matrix[i] = calloc(spalte , sizeof(int));
		if(matrix[i] == NULL)
			return -1;
	}

	for(i = 0; i < zeile; i++){
		for(j = 0; j < spalte; j++)
			printf("%d", *(*(matrix + i) + j));
		printf("\n");
	}

	//freeing
	for(i = 0; i < zeile; i++)
		free(matrix[i]);
	free(matrix);
	return 0;
}	
