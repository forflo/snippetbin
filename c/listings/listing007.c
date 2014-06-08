#include <stdio.h>
#include <stdlib.h>

int main(void){
	printf("%llx\n", sizeof(int));
	printf("%llx\n", sizeof(int *));
	printf("%llx\n", sizeof(int **));
	printf("%llx\n", sizeof(int ***));
	printf("%llx\n", sizeof(float));
	printf("%llx\n", sizeof(float *));
	printf("%llx\n", sizeof(float **));
	printf("%llx\n", sizeof(char));
	printf("%llx\n", sizeof(char *));
	printf("%llx\n", sizeof(char **));
	printf("%llx\n", sizeof(char ***));
	printf("%llx\n", sizeof(char ****));
}
