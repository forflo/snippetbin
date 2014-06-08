#include <stdio.h>
#include <stdlib.h>

int main(void){
	double *dptr = 0;

	while (1) 
		dptr = malloc(100 * sizeof(double));

	printf("Speicherfehler\n");
	int b;
	scanf("%d", &b);
	return EXIT_SUCCESS;
}
