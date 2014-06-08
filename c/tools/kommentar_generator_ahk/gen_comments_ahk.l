/*
Autor: Florian Mayer
Datum: 6. Semester WIF (2013)
Zweck: Dieses kleine Werkzeug scannt eine AHK-Code-Datei nach
Definitionen für Hotkeys, Hotstrings, Funktionen und Klassen
und schreibt diese Definitionen strukturiert in eine HTML-Datei.
Installation: Lex auf diese Datei ausführen und die C-Datei
mithilfe eines geeigneten Compilers und der Bibliothek glib 
übersetzen und linken!
*/

%{
#include <stdio.h>
#include <stdlib.h>
#include <glib.h>

#define HK 0
#define HS 1
#define FU 2
#define CL 3
#define N 4
%}

hkkeys ("^"|"+"|"!"|"<"|">"|"#")
ident [a-zA-Z\-\_][a-zA-Z\-\_0-9]*
func {ident}" "*"("
class "class"" "*{ident}" "*"{"
hk {hkkeys}+[a-zA-Z]"::"
hs "::"{ident}"::"
aais ([^;]*|";"[^<;])*
com ";>>>"{aais}\r\n";<<<"\r\n
funcCom {com}{func} 
classCom {com}{class} 
hkCom {com}{hk} 
hsCom {com}{hs} 


%%

{funcCom} { return FU; } 
{classCom} { return CL; }
{hkCom} { return HK; }
{hsCom} { return HS; }

%%

void initOutput(FILE *file){
	fprintf(file, "<?xml version=\"1.0\" encoding=\"UTF-8\" ?>\n");
	fprintf(file, "<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Strict//EN\" \
     			\"http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd\">\n");
	fprintf(file, "<html xmlns=\"http://www.w3.org/1999/xhtml\">\n");
	fprintf(file, "\t<head>\n\t\t<title>Kommentare</title>\n\t</head>\n");
	fprintf(file, "\t<body>\n");
	fflush(file);
}

void printTable(FILE *file, GPtrArray *comments, GPtrArray *names, char *type, char *title){
	int i, j;
	fprintf(file, "<h3> %s </h3>\n", title);
	fprintf(file, "<table border=\"1\">\n");

	fprintf(file, "<tr><th>%s</th>\n", type);
	fprintf(file, "<th>Kommentar</th></tr>\n");
	for(i=0; i<comments->len;i++){
		fprintf(file, "<tr>\n");
		fprintf(file, "<td>%s</td>\n", (char *) g_ptr_array_index(names,i));
		fprintf(file, "<td>%s</td>\n", (char *) g_ptr_array_index(comments, i));
		fprintf(file, "</tr>\n");
	}	
	fprintf(file, "</table>\n");
	fflush(file);
}

void endOutput(FILE *file){
	fprintf(file, "\t</body>\n</html>");
	fclose(file);
}

/* return NULL if failure*/
char *getName(char *temp){
	int i=0, j;
	char *result;
	gchar **string = g_strsplit(temp, "\n", -1);
	while(string[i] != NULL){
		if(string[i][0] != ';'){
			result = (char *) malloc(sizeof(char) * strlen(string[i]));
			for(j=0; j< strlen(string[i]); j++)
				result[j] = string[i][j];
			return result;
		}
		i++;
	}
	return NULL;
}


char *getComment(char *temp){
        int i=0, j;
        GString *result = g_string_new("");
        gchar **string = g_strsplit(temp, "\n", -1);
        while(string[i] != NULL){
                if (string[i][0] == ';' && (string[i][1] == '>' || string[i][1] == '<')) {
                        for(j=4; j<strlen(string[i]); j++)
                                g_string_append_c(result,string[i][j]);
                        g_string_append(result, " ");
                } else if (string[i][0] == ';' && (string[i][1] != '>' || string[i][1] != '<')) {
                        for(j=2; j<strlen(string[i]); j++)
                                g_string_append_c(result, string[i][j]);
                        g_string_append(result, " ");
                } else { }
                        /* nothing */

                i++;
        }
        return result->str;
}


int main(){
	int i, c;
	char *pfad = "out.xhtml";
	FILE *output = fopen(pfad, "w+");

	if(output == NULL){
		printf("Datei konnte nicht geöffnet werden");
		return EXIT_FAILURE;
	}

	initOutput(output);

	GPtrArray *funcComments = g_ptr_array_new();
	GPtrArray *funcNames = g_ptr_array_new();
	GPtrArray *classComments = g_ptr_array_new();
	GPtrArray *classNames = g_ptr_array_new();
	GPtrArray *hkComments = g_ptr_array_new();
	GPtrArray *hkNames = g_ptr_array_new();
	GPtrArray *hsComments = g_ptr_array_new();
	GPtrArray *hsNames = g_ptr_array_new();

	do {
		c = yylex();
		switch(c){
			case HK:
				g_ptr_array_add(hkNames, (gpointer) getName(yytext));
				g_ptr_array_add(hkComments, (gpointer) getComment(yytext));
				printf("HK\n");
				break;
			case HS:
				g_ptr_array_add(hsNames, (gpointer) getName(yytext));
				g_ptr_array_add(hsComments, (gpointer) getComment(yytext));
				printf("HS\n");
				break;
			case CL:
				g_ptr_array_add(classNames, (gpointer) getName(yytext));
				g_ptr_array_add(classComments, (gpointer) getComment(yytext)); 
				printf("CL\n");
				break;
			case FU:
				g_ptr_array_add(funcNames, (gpointer) getName(yytext));
				g_ptr_array_add(funcComments, (gpointer) getComment(yytext));
				printf("FU\n");
				break;
		}
	} while (!feof(stdin));
	
	printTable(output, hkComments, hkNames, "Hotkey", "Hotkey-Kommentare");
	printTable(output, hsComments, hsNames, "Hotstring", "Hotstring-Kommentare");
	printTable(output, classComments, classNames, "Klassen", "Klassenkommentare");
	printTable(output, funcComments, funcNames, "Funktionen", "Funktionskommentare");
	
	endOutput(output);
	return EXIT_SUCCESS;
}


