#include <gmp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

mpz_t *fak(int n){
	int i;

	mpz_t *result = malloc(sizeof(mpz_t) * 1);;
	mpz_init_set_str(*result, "1", 10);
	for(i=1; i<n; i++)
		mpz_mul_si(*result, *result, (long) i + 1);
	return result;
}

int main(int argc, char **argv){
	if(argc!=2){
		printf("usage: %s natural number\n", argv[0]);
		return EXIT_FAILURE;
	}
	
	gmp_printf("Value: %Zd\n", fak(atoi(argv[1])));
	return EXIT_SUCCESS;
}
