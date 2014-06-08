#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[], char **envp){
	int i = 0;
	while(envp[i] != NULL){
		printf("Env-Variable NR: %d\n", i);
		printf("%s\n", envp[i++]);
	}
	return EXIT_SUCCESS;
}

