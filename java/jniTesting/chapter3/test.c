#include <stdio.h>

int main(void){
	char buf[122];
	scanf("%s", buf);
	printf("%s", buf);
	char i;
	for (i = -128; i < 127; i++){
		printf("%c",  i);
	}
	return 0;
}
