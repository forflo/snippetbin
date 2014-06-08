#include <stdio.h>
#include <stdlib.h>

int main(void){
	int i, j, k;
	for(i = 0, j = 0, k = 0; i < 10; i++, j--, k+=2){
		printf("i = %d ", i);
		printf("j = %d ", j);
		printf("k = %d \n", k);
	}
}
