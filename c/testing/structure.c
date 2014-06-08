#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct abc {
	char a;
	int b;
	char c;
};

void use_abc(struct abc *s);

int main(void){
	struct abc *a = (struct abc *) malloc(sizeof(struct abc) * 1);	
	a->a = 'a';
	a->b = 'b';
	a->c = 'c';
	use_abc(a);
	return EXIT_SUCCESS;
}

void use_abc(struct abc *s){
	printf("A: %c - B: %c - C: %c\n", s->a, (char) s->b, s->c);	
}
