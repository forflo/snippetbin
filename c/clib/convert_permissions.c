/* Converts a given string into the binary representation of an octal unix permission code */
#include <math.h>
#include <string.h>

int convert_permissions(char *permissions){
	int i, j=0, r=0, res=0;
	/* Umwandlung der Zeichenkette in eine binär gespeicherte Oktalzahl */
	/* Erst in eine Oktalzahl im Zehnersystem ... */
	for (i=strlen(permissions)-1; i>=0; i--){
		if(permissions[i] < 48 || permissions[i] > 57){
			return -1;
		}   
		r += pow(8, j++) * (permissions[i]-48);
	}   
	/* ... dann in eine Zahl im Zweiersystem */
	j=0;
	do {
		i = r%2;
		res += pow(2, j++) * i;
	} while(r/=2);
}
