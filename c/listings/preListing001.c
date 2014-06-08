#include <stdio.h>
#include <stdlib.h>

#ifdef __APPLE__
	#define SYS "Code für Apple-Rechner"
#elif __linux__
	#define SYS "Code für linux-Rechner"
#else
	#define SYS "Code für sonstige Rechner"
#endif

int main(void){
	printf("%s", SYS);
	return EXIT_SUCCESS;
}
