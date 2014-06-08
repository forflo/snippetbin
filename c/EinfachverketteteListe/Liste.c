/*Nicht Vollständig !!*/
/*
Grundlegende Funktionden für den Abstrakten  Datentyp "Verkettete Listen"
Beinhaltet:
	-initListe
	-popX 		(Gibt das X-te Element, sofern vorhanden, 
			 aus und löscht es aus der Liste)
	-popFront 	(Gibt das erste Element aus und entfernt es)
	-popBack 	(Gibt das letzte Element aus und ent. es)
	-pushFront	(Setzt ein element von vorne ein)
	-pushBack	(erklärt sich selbst)
	-printListe	(ebenda)

Mögliche Erweiterungen:
	-Liste in eine Datei schreiben
	-Liste aus einer Datei in den Arbeitsspeicher schreiben
	-Jeder Listenknoten ist zugleich ein Listenkopf für eine weitere Liste
	-Jeder Listenknoten enthält zwei next Zeiger --> Binärer Baum





#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define LAENGE 80

typedef struct s_element {
	char inhalt[LAENGE];
	struct s_element *next;
} t_element;

typedef struct {
	struct s_element *erstesElement;
	struct s_element *letztesElement;
	int anzahlElemente;
}t_Listenkopf;

*/

void initListe(t_Listenkopf *li);
void pushFront(t_Listenkopf *li, char *str);
void pushBack(t_Listenkopf *li, char *str);
void printListe(t_Listenkopf *li);
void popFront(t_Listenkopf *li,char *str);
void popBack(t_Listenkopf *li,char *str);
void popX(t_Listenkopf *li,char *str,int x);

int popFront(t_Listenkopf *li,char *str){
	t_element *zeigerhilf1;
	if(li->anzahlElemente==0 || li->erstesElement==NULL){
		return 0;
	} else if(li->anzahlElemente==1){
		strcpy(str,li->erstesElement->inhalt);
		free(li->erstesElement);
		li->erstesElement=NULL;
	} else {
		strcpy(str,li->erstesElement->inhalt);
		if(li->anzahlElemente==2){
			free(li->erstesElement);
			li->erstesElement=NULL;
		} else {
			zeigerhilf1=li->erstesElement->next;
			free(li->erstesElement);
			li->erstesElement=zeigerhilf1;
		}
	}
	li->anzahlElemente--;
}

void popBack(t_Listenkopf *li,char *str){
	t_element *zeigerhilf1;
	if(li->anzahlElemente==0 || li->letztesElement==NULL){
		return 0;
	} else if(li->anzahlElemente==1){
		strcpy(str,li->letztesElement->inhalt);
		free(li->letztesElement);
		li->letztesElement=NULL;
	} else {
		strcpy(str,li->letztesElement->inhalt);
		if(li->anzahlElemente==2){
			free(li->letztesElement);
			li->letztesElement=NULL;
			li->erstesElement->next=NULL;
		} else {
			li->letztesElement=NULL;

		}
	}
	li->anzahlElemente--;
}

void popX(t_Listenkopf *li,int x, char *str){



	li->anzahlElemente--;
}

void initListe(t_Listenkopf *zeiger1){
	zeiger1->erstesElement=NULL;
	zeiger1->letztesElement=NULL;
	zeiger1->anzahlElemente=0;
}

void pushFront(t_Listenkopf *li, char *str){
	t_element *zeigerhilf1;
	t_element *element;
	element=malloc(sizeof(t_element));
	strcpy(element->inhalt,str);
	if (li->anzahlElemente==0){
		li->erstesElement=element;
		element->next=NULL;
	} else if(li->anzahlElemente==1){
		if(li->erstesElement!=NULL){
			li->letztesElement=li->erstesElement;
			li->erstesElement=element;
			element->next=li->letztesElement;
		} else {
			li->erstesElement=element;
			element->next=li->letztesElement;
		}
	} else {
		zeigerhilf1=li->erstesElement;
		li->erstesElement=element;
		element->next=zeigerhilf1;
	}
	li->anzahlElemente++;
}

void pushBack(t_Listenkopf *li, char *str){
	t_element *zeigerhilf1;
	t_element *element;
	element=malloc(sizeof(t_element));
	strcpy(element->inhalt,str);
	if (li->anzahlElemente==0){
		li->letztesElement=element;
		element->next=NULL;
	} else if(li->anzahlElemente==1){
		if (li->letztesElement==NULL){
			li->letztesElement=element;
			li->erstesElement->next=element;
			element->next=NULL;
		} else {
			li->erstesElement=li->letztesElement;
			li->erstesElement->next=element;
			li->letztesElement=element;
			element->next=NULL;
		}
	} else {
		zeigerhilf1=li->letztesElement;
		zeigerhilf1->next=element;
		li->letztesElement=element;
		element->next=NULL;
	}
	li->anzahlElemente++;
}

void printListe(t_Listenkopf *li){
	int a=0;
	t_element *zeigerhilf2;
	t_element *zeigerhilf1;
	zeigerhilf1=li->erstesElement;
	while(zeigerhilf1!=NULL){
		printf("Element %i:",a);
		printf("%s",zeigerhilf1->inhalt);
		printf("\n");
		zeigerhilf2=zeigerhilf1;
		zeigerhilf1=zeigerhilf2->next;
		a++;
	}
}

//Diese ist eine test-main
/*
int main(void){
	t_Listenkopf *mylist;
	char gutentag[]="Hallo ich heise flo";
	int c,d;
	mylist=malloc(sizeof(t_Listenkopf));
	initListe(mylist);
	pushBack(mylist,"1");
	pushBack(mylist,"2");
	pushBack(mylist,"3");
	pushBack(mylist,"4");
	printListe(mylist);
	printf("\nErstes Element:%s",mylist->erstesElement->inhalt);
	printf("\nLetztes Element:%s",mylist->letztesElement->inhalt);
	free(mylist);
	return 0;
}
*/
