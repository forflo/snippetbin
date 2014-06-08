%{

#include <stdlib.h>
#include <stdio.h>
#include "str_dyn.h"

int bl = 0;
char *code;

%}

%x blockcomment linecomment fce

%%

"[[[" { 
	/** 
	 Token: FCECODE
	 This Token is identified by the unique string "[[[" in the Code.
	 This Code will move the foreign code into an dynamically growing string structure.
	*/

	int next;
	dyn_string_t *buffer = ds_get();
	int index = 0, c = 0;
	do {
		next = input();
		if(next == ']') c++;
		else c=0;
		ds_append_char(buffer, (char) next);
		if(c == 3) break;
	} while(!feof(yyin));
	code = buffer->data;
	ds_free(buffer);
	return(3);
}

"//" {BEGIN(linecomment);}
<linecomment>[^\n]* {printf("%s\n", yytext);} /* eat up everything except newline */
<linecomment>\n {BEGIN(INITIAL); return(2);}

"/*" {BEGIN(blockcomment);}
<blockcomment>"*"+"/" {BEGIN(INITIAL); return(1);} /* Eat up all block comments */
<blockcomment>("*"[^*/]|[^*])* {printf("%s\n", yytext);} /* eat every * not followed by /*/

%%

int main(void){
	do {
		int result = yylex();
		if(result == 1){
			printf("Ein Blockkommentar konnte gelesen werden!\n");
			printf("Zeilen:%d", bl);
			bl = 0;
		} else if(result == 2){
			printf("Ein Zeilenkommentar konnte gelesen werden!\n");
		} else if (result ==3){
			printf("FCE-Code konnte erkannt werden:\nAnfang[%s]Ende\n", code);	
		}	
	} while(!feof(stdin));
}

