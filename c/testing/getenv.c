#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
	if (argc != 2){
		fprintf(stdout, "Bitte geben Sie einen Variablennamen an!\n");
		return EXIT_FAILURE;
	} else {
		printf("%s\n", getenv(argv[1]));
	}
	return EXIT_SUCCESS;
}
