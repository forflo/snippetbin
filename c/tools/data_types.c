#include <stdio.h>

int main(void){
	printf("Im Folgenden wird eine Liste von elementaren C-Datentypen und deren Platzbelegungen ausgegeben.\n");

	printf("Größe von Zeiger void:%ld\n", sizeof(void *));
	printf("Größe von Zeiger int:%ld\n", sizeof(int*));
	printf("Größe von Zeiger long:%ld\n", sizeof(long*));
	printf("Größe von Zeiger long long:%ld\n", sizeof(long long*));
	printf("Größe von Zeiger double:%ld\n", sizeof(double*));
	printf("Größe von Zeiger float:%ld\n", sizeof(float*));
	printf("Größe von Zeiger char:%ld\n", sizeof(char*));
	printf("Größe von Zeiger long double:%ld\n", sizeof(long double*));


	printf("Größe von void:%ld\n", sizeof(void));
	printf("Größe von int:%ld\n", sizeof(int));
	printf("Größe von long:%ld\n", sizeof(long));
	printf("Größe von long long:%ld\n", sizeof(long long));
	printf("Größe von double:%ld\n", sizeof(double));
	printf("Größe von float:%ld\n", sizeof(float));
	printf("Größe von char:%ld\n", sizeof(char));
	printf("Größe von long double:%ld\n", sizeof(long double));
}
