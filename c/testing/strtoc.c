#include <string.h>
#include <stdio.h>
#include <stdlib.h>

char *str_tok(const char *string, const char *delimiters){
	static int pr = 0, sp = 0;
	static int fin = 0;
	int i;
	while(*(string+sp) != '\0'){
		for(i=0; i<strlen(delimiters);i++){
			if(*(string+sp) == *(delimiters+i)){
				char *result = (char *) malloc((sp - pr + 1) * sizeof(char));	
				strncpy(result, string + pr, sp - pr);
				result[sp - pr] = '\0';
				pr = sp++ + 1;
				return result;
			}
		}
		sp++;
	}

	if(fin != 1){
		char *result = (char *) malloc((sp - pr + 1) * sizeof(char));
		strncpy(result, string + pr, sp - pr);
		result[sp - pr] = '\0';
		fin = 1;
		return result;
	} else {
		pr=0, sp=0, fin=0;
		return NULL;
	}
}


int main(void){
	char *temp;
	while((temp=str_tok("Hallo Du:Bist,Doof", " :,")) != NULL){
		printf("Token: %s\n", temp);
	}
	while((temp=str_tok("Urghaeiieirier:,ifdafer:urieieieiierrer:fiieriuuier", ":,")) != NULL){
		printf("Token: \"%s\"\n", temp);
	}
	return EXIT_SUCCESS;
}


