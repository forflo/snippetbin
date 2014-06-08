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

void ***get3Dim(int zeile, int spalte, int tiefe){
	int i, j;
	void ***matrix;
	matrix = malloc(zeile * 8);
	
	if (matrix == NULL){
		printf("[get3Dim]: Keine Speicherallokierung mehr möglich \n");
		return NULL;
	}
	
	for(i = 0; i < zeile; i++){
		*(matrix + i) = malloc(spalte * 8);
		if( *(matrix + i) == NULL){
			printf("[get3Dim]: Keine Speicherallokierung mehr möglich\n");
			return NULL;
		}
	}
	
	for(i = 0; i < zeile; i++){
		for ( j = 0; j < spalte; j++) {
			*(*(matrix + i) + j) = malloc(tiefe * 8);
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

int main(void){
	int i, j, k, zeile, spalte, tiefe;
	int ***matrix;

	printf("Bitte geben sie die Zeilen ein: ");
	scanf("%d", &zeile);
	printf("Bitte geben sie die Spalten ein: ");
	scanf("%d", &spalte);
	printf("Bitte geben sie die Tiefe ein: ");
	scanf("%d", &tiefe);

	matrix = (int ***) get3Dim(zeile, spalte, tiefe);
	
	for(i = 0; i < zeile; i++)
		for(j = 0; j < spalte; j++)
			for(k = 0; k < tiefe; k++){
				*(*(*(matrix + i) + j) + k) = i + j + k;
				printf("matrix[%d][%d][%d] = %i\n", i, j, k, *(*(*(matrix + i) + j) + k));
			}

	free3Dim(matrix, zeile,spalte, tiefe);

	return EXIT_SUCCESS;
}
