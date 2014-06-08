#include <stdio.h>
#include <stdlib.h>
#define BLKSIZE 8

int main(void){
	int n = 0, max = BLKSIZE, z, i;
	int *zahlen;

	zahlen = calloc(BLKSIZE, sizeof(int));
	if (zahlen == NULL){
		printf("Kein virtueller RAM mehr vorhanden");
		return EXIT_FAILURE;
	}
	
	printf("Zahlen eingeben --- Beenden mit 0\n");
	while(1){
		printf("Zahl (%d) eingeben : ", n+1);
		scanf("%d",&z);
		if (z == 0) break;
		if(n >= max-1){
			max+=BLKSIZE;
			zahlen = realloc(zahlen, max*sizeof(int));
			if(NULL == zahlen){
				printf("Kein virtueller RAM mehr vorhanden !");
				return EXIT_FAILURE;
			}
			printf("Neuer Speicher 	: %d Bytes\n", BLKSIZE);
			printf("Insgesamt	: %d Bytes\n", sizeof(int) * max);
			printf("Platz für 	: %d Elemente\n", max);
		}
		*(zahlen+ n++) = z;
	}
	printf("Folgende Zahlen wurden eingegeben -> \n\n");
	for(i = 0; i < n ; i++)
		printf("%d ", *(zahlen + i));
	printf("\n");
	return EXIT_SUCCESS;
}
