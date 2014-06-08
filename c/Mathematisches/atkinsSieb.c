#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[]){
	char *gestrichen = malloc(atoi(argv[1]) * 8);
	long cou = (long) atoi(argv[1]);
	long cnt = 0;
	
	long i;
	for(i = 2; i < cou; i++){
		gestrichen[(int) i] = 'n';
	}
	
	for(i = 2; i < cou; i++){
		if(gestrichen[(int) i] == 'n') {
			printf("%d ,", (int) i);
			cnt++;
			long j;
			for(j = i*i; j < cou; j+=i){
				gestrichen[(int) j] = 'j';
			}
		}
	}
	printf("\nEs wurden %d Primzahlen berechnet", (int) cnt);
}
