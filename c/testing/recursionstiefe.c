#include <stdio.h>
#include <unistd.h>

int count = 0;
int count2 = 0;

void rec();
void rec2();

void rec(){
	count++;
	printf("Aktuell: %d\n", count);	
	if(count == 520000){
		printf("Schlafen\n");
		sleep(10);
		rec2();
	}
	rec();
}

void rec2(){
	count2++;
	printf("Aktuell (2): %d\n", count2);
	if(count2 ==(520000)){
		printf("Schlafen2\n");
		sleep(10);
	}
	rec2();
}

int main(void){
	rec();
}
