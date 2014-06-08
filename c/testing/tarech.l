%{

#include "tarech.tab.h"
#include <string.h>
#include <stdlib.h>
extern YYSTYPE yylval;

%}

Ziffer [0-9]
Zahl {Ziffer}+
delim [ \t\n]


%%

{delim} {/*eat up delimiters*/}

";" {return(END);}
"+" {return(ADD);}
"-" {return(SUB);}
"*" {return(MUL);}
"/" {return(DIV);}
"(" {return(KLAUF);}
")" {return(KLZU);}
"**" {return(POT);}
{Zahl} 	{ yylval.i = atoi(yytext); return(ZAHL); }

%%
