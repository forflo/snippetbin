#include <stdio.h>
#include <string.h>

const int Spalten=120;
const int Zeilen=6;
/*Gibt den Tabulaturblock auf dem Bildschrim aus*/ 
void output_tab(char tab[][Spalten]){
	int i,j; for(i=0;i<Zeilen;i++){
	for(j=0;j<Spalten;j++) 
		printf("%c",tab[i][j]);
	printf("\n"); }
	for(i=0;i<Spalten;i++) 
		printf("#");
	printf("\n"); }
/*Blankt den Tabulaturblock*/
void clear_tab(char str[][Spalten]){
	char saiten[6]="eHGDAE"; 
	int z=0,i,j; 
	for(j=0;j<Zeilen;j++){
		str[j][0]=saiten[z++]; 
		str[j][1]='|'; 
		for(i=2;i<Spalten;i++)
			str[j][i]='-';
		}
	}
/*Schreibt einen Tabulaturblock als Anhang in die Datei "tabulatur.txt" im Programmverzeichnis*/ 
int write_tab_to_disk(char tab[][Spalten]){
	int i,j;
	FILE *datei; 
	datei=fopen("tabulatur.txt","a+"); 
	for(i=0;i<Zeilen;i++){
		for(j=0;j<Spalten;j++) 
			fputc(tab[i][j],datei);
		fputc('\n',datei); }
		for(i=0;i<Spalten;i++) 
			fputc('#',datei);
		fputc('\n',datei);
	return 1; }
	/*Hauptaufgabe: Schreibt die einzelnen noten, bzw. Akkorde in den Tab-Block und behandelt die Ausgabe auf den
	Bildschrim und das Schreiben in die Datei*/
int put_display_notes(char *dateiname,char tab[][Spalten],int knopf){
	FILE *datei;
	int a,b=0,sp_nr=3,bund;
	char buffer,erlaubte_zeichen[]="eHGDAE",erlaubte_zahlen[]="0123456789"; 
	if((datei=fopen(dateiname,"r+"))==NULL){
		printf("Datei konnte nicht geoeffnet werden\n");
		return 0; 
	}
	while((buffer=fgetc(datei))!=EOF){ 
		while(buffer!='\n'){
			for(a=0;a<6;a++) 
				if(buffer==erlaubte_zeichen[a]){
					bund=a;
					continue; 
				}
			for(a=0;a<10;a++) 
				if(buffer==erlaubte_zahlen[a]){
					tab[bund][sp_nr]=erlaubte_zahlen[a];
					continue; 
				}
			buffer=fgetc(datei); 
		}
	/*
	Hier wird gecheckt ob schon ein Tabulaturblock voll ist, wenn ja wird er ausgegeben, und bei
	bedarf in die Datei geschrieben
	*/
		if(sp_nr>=Spalten-1){ 
			output_tab(tab);
			if(knopf==1) 
				write_tab_to_disk(tab);
			clear_tab(tab);
			sp_nr=1; 
			b++; 
		}
		sp_nr+=2; 
	}
	/*
	Hier wird gechekct ob entweder ein Rest in die Datei bzw auf den Bildschrim zu schreiben ist oder nur ein Tabulatur-
	Block zu einem Teil gefüllt wurde
	*/
	if(b==0 || sp_nr<Spalten-1){
		output_tab(tab); 
		if(knopf==1)
			write_tab_to_disk(tab);
	} 
	fclose(datei); 
	return 1;
}

int main(void){
	char tab[Zeilen][Spalten],dateiname[30];
	int knopf,i=1;
	clear_tab(tab);
	printf("Bitte geben sie die Noten-Datei an:\n");
	scanf("%s",dateiname); 
	printf("In Datei schreiben?\n1/ja 0/nein:\n"); 
	scanf("%i",&knopf); 
	put_display_notes(dateiname,tab,knopf);
	return 0;
}
