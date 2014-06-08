#include <stdio.h>
#include <ffi.h>
#define MAX_SIZE 8

int main(void){
	/* cif = call interface */
	ffi_cif cif;
	ffi_type *args[1];
	void *values[1];
	char *s;
	void *rc = malloc(MAX_SIZE);

	args[0] = &ffi_type_pointer;
	values[0] = &s;

	if(ffi_prep_cif_var(&cif, FFI_DEFAULT_ABI, 1, &ffi_type_uint, args) == FFI_OK){
		s = "Hello World!";
		ffi_call(&cif, puts, rc, values);

		s = "This is cool!";
		ffi_call(&cif, puts, rc, values);
	} else {
		printf("Fehler!\n");
		exit(1);
	}

	printf("Return value of call: %d\n", *((int *) rc));

	return 0;
}
