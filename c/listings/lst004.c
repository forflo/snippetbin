#include <stdio.h>
#include <stdlib.h>


int main(void){
	int i, j , zeile, spalte;
	int **matrix;

/*
	printf("Wie viele Zeilen: ");
	scanf("%d", &zeile);
	printf("Wie viele Spalten: ");
	scanf("%d", &spalte);
*/
	for(i = 0; i < 100; i++) {
	
		zeile = i;
		spalte = i;
		
		matrix = malloc(zeile * sizeof(int*));
		if ( matrix == NULL ) {
			printf("Error in 1\n");
			return EXIT_FAILURE;
		}
		
		for( i = 0; i < zeile; i++ ){
			matrix[i] = malloc(spalte * sizeof(int));
			if (matrix[i] == NULL){
				printf("Error in 2\n");
				return EXIT_FAILURE;
			}
		}
	
		printf("Hier NR a\n");
		for( i = 0; i < zeile; i++)
			for( j = 0; j < spalte; j++){
				printf("i = %d, j = %d\n", i, j);
				matrix[i][j] = i+j;
			}
	
		printf("Hier NR b\n");
		for(i = 0; i <zeile; i++){
			for(j = 0; j<spalte; j++)
				printf("%d ", matrix[i][j]);
			printf("\n");
		}
	}
	return EXIT_SUCCESS;
}
