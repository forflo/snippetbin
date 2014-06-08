#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 1000 

//deklaration eines neuen types namens "id3"
typedef struct id3_tag {
	char titel[30],	interpret[30], album[30];
	short jahr;
	char kommentar[30], genre[30];
} id3;

//deklaration der struktur id4_tag
//kann entweder über "struct id4_tag bezeichner"
//oder...
struct id4_tag {
	char tit[4], inter[40];
	short jahr;	
};

//"id4 bezeichner" definiert werden !
typedef struct id4_tag id4;



id3 *dummy_init_id3_ref(void){
	id3 *tmp = malloc(sizeof(id3));
	if(tmp == NULL) {
		printf("[dummy_init_id2_ref] Kein Speicherplatz bekommen...");
		exit(EXIT_FAILURE);
	}
	strcpy(tmp->titel, "titel");
	strcpy(tmp->interpret, "interpret");
	strcpy(tmp->album, "album");
	tmp->jahr = 2344;
	strcpy(tmp->kommentar, "kommentar");
	strcpy(tmp->genre, "bla");

	return tmp;
}

id3 dummy_init_id3(void){
	id3 tmp;
	strcpy(tmp.titel, "titel");
	strcpy(tmp.interpret , "interpret");
	strcpy(tmp.album , "album");
	tmp.jahr = 2009;
	strcpy(tmp.kommentar , "kommentar");
	strcpy(tmp.genre , "genre");
	return tmp;
}

void print_delimiter(char *text, char *delimiter){
	printf("%s%s%s\n", delimiter, text, delimiter);
}

void print_id3(id3 tag){
	char *delimiter = "--------------";
	char *text = "start printig id3";

	print_delimiter(text, delimiter);
	printf("%s\n", tag.titel);
	printf("%s\n", tag.interpret);
	printf("%s\n", tag.album);
	printf("%d\n", tag.jahr);
	printf("%s\n", tag.kommentar);
	printf("%s\n", tag.genre);
	print_delimiter("end printing", delimiter);
}

void print_id3_ref(id3 *tag){
	char *delimiter= "#############";
	print_delimiter("start printing id3", delimiter);
	printf("%s\n", tag->titel);
	printf("%s\n", tag->interpret);
	printf("%s\n", tag->album);
	printf("%d\n", tag->jahr);
	printf("%s\n", tag->kommentar);
	printf("%s\n", tag->genre);
	print_delimiter("end printing", delimiter);
}

int main(void){
	/*
	 + Beispiele der verschiedenen
	 + definitionsarten ...
	*/
	int i;
	id3 data1 = {};
	id3 data2 = {"bla", "blabla", "a", 2009, "b", "c"};
	id3 data3 = {.titel = "bla", .jahr = 9999};
	print_id3(data1);
	print_id3(data2);
	print_id3(data3);
	print_id3_ref(&data2);
	id3 id3tag1 = dummy_init_id3();
	id3 id3tag2 = *dummy_init_id3_ref();
	struct id4_tag id4tag1;
	id4 id4tag2;
	print_id3(id3tag1);
	print_id3(id3tag1);

	//erstellung eines arrays von Zeigern
	id3 **data;
	//dieses array hat MAX Plätze für Zeiger
	data = malloc(MAX);
	for(i = 0; i < MAX; i++)
		*(data + i) = dummy_init_id3_ref(); //Zuweisung der Zeiger...
	for(i = 0; i < MAX; i++)
		print_id3_ref( *(data+i) ); 


	return 0;
}

