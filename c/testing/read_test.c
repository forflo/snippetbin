#include <stdio.h>
#include <stdlib.h>

#define MAX 100

/*
fgets(buffer, n, stdin)
liest von stdin n - 1 Zeichen ein
und hängt an den Buffer das Zeichen '\0'
zum Abschluss. 
*/

int main(int argc, char *argv[]){
	char buffer[10];
	printf("Geben Sie nun etwas ein:\n");
	fgets(buffer, 10, stdin);
	printf("Sie gaben ein: %s\n", buffer);
	return EXIT_SUCCESS;
}
