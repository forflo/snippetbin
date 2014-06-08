#include <stdio.h>
#include <ffi.h>

int main(void){
	/* cif = call interface */
	ffi_cif cif;
	ffi_prep_cif(&cif, FFI_DEFAULT_ABI, 2
}
