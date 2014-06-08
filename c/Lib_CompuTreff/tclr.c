#include <stdio.h>
void tclr(void){
	fprintf(stdout, "\033[2J");
	fprintf(stdout, "\033[1;1H");
}
