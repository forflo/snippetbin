#include <stdio.h>
#include <sqlite3.h>
#include <stdlib.h>

int main(void){
	int max = 1000;
	FILE *pic;
	if ((pic=fopen("city.png","r")) == NULL){
		printf("Fehler beim Öffnen der Datei!");
	}
	
	fseek(pic, 0, SEEK_END);
	int size = ftell(pic);
	rewind(pic);
	char *buffer = (char *) malloc(size * sizeof(char));

	int read = fread(buffer, size, 1, pic) ;
	if(read != 1){
		printf("Fehler beim lesen der Datei\n");
		return EXIT_FAILURE;
	}

	fwrite(buffer, size, 1, stdout);
	return EXIT_SUCCESS;
}
