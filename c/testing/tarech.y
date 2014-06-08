%{

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "baum.h"

struct knoten *wurzel;
gen_count = 0;
int tarech(struct knoten *wurzel);

%}

%union {
	int i;
	struct knoten *knot;
}

%token <i> ZAHL
%token END KLAUF KLZU
%left ADD SUB
%left MUL DIV
%right POT
%type <knot> expr eval_exp



%%

s			: expr END { wurzel = $1; }
			;

expr		: expr ADD expr {$$ = erzeuge_knoten(0, '+', 0, $1, $3);}
			| expr SUB expr {$$ = erzeuge_knoten(0, '-', 0, $1, $3);}
			| expr MUL expr {$$ = erzeuge_knoten(0, '*', 0, $1, $3);}
			| expr DIV expr {$$ = erzeuge_knoten(0, '/', 0, $1, $3);}
			| expr POT expr {$$ = erzeuge_knoten(0, '^', 0, $1, $3);}
			| eval_exp
			; 

eval_exp 	: KLAUF expr KLZU {$$ = $2;}
			| ZAHL {$$ = erzeuge_knoten($1, ' ', 1, NULL, NULL);}
			;

%%

yyerror(void){
	printf("Syntaxfehler!");
}

int main(void){
	int result = 0;
	yyparse();
	result = traverse(wurzel);
	printf("Das Ergebnis des Ausdrucks: %d\n", result);
}


void convert_to_graphviz(struct knoten *wurzel){
	struct knoten *next = wurzel-> ;
	struct knoten *cur = wurzel;
	struct knoten *prev;
	while(1){
		if(!(wurzel->leaf)){
			prev = cur;
			cur = 
		} else {

		}
	}
}

int traverse(struct knoten *wurzel){
	if(!wurzel->leaf){
		switch(wurzel->operation){
			case '*':
					return traverse(wurzel->left) * traverse(wurzel->right);
				break;
			case '+':
					return traverse(wurzel->left) + traverse(wurzel->right);
				break;
			case '-':
					return traverse(wurzel->left) - traverse(wurzel->right);
				break;
			case '/':
					return traverse(wurzel->left) / traverse(wurzel->right);
				break;
			case '^':
					return pow(traverse(wurzel->left), traverse(wurzel->right)); 
				break;
			default:
				printf("Ein Fehler ist beim Berechnen des Ausdrucks aufgetreten!!!\n");
				break;
		}
	} else {
		return wurzel->wert;
	}
}
