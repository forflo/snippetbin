#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
	
	char *str = malloc(20 * 8);
	char *str2 = malloc(20 * 8);
	str = "iii ";
	str2 = "fff ";

	char concat[50] = "";
	
	strcat(concat, str);
	strcat(concat, str2);
	printf("%s\n", concat);
}
