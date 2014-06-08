/*
This little program repeats the given
char the given times on stdout
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]){
	int i, num;
	char *buffer;
	if (argc != 3) {
		printf("usage: %s <the number of times to repeat> <a char>\n", argv[0]);
		return EXIT_FAILURE;
	}
	if (strlen(argv[2]) != 1)
		printf("usage: %s <the number of times to repeat> <a char>\n", argv[0]);
	num = atoi(argv[1]);
	buffer = (char *) malloc(sizeof(char) * (num + 1));
	for(i=0; i<num; i++)
		buffer[i] = argv[2][0];
	buffer[num] = '\0';
	
	printf("%s", buffer);
	return EXIT_SUCCESS;
}
