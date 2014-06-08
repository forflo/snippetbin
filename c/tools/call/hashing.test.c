#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <CUnit/Console.h>
#include <stdio.h>
#include <string.h>
#include "hashing.h"

void test_hashing(void){
	int i;
	CU_ASSERT(! strcmp("598d4c200461b81522a3328565c25f7c", get_hash("hallo")));
}


int main(void){
	CU_pSuite pS = NULL;
	if (CUE_SUCCESS != CU_initialize_registry())
		return CU_get_error();

	pS = CU_add_suite("Suite_hash", NULL, NULL);
	if (NULL == pS){
		CU_cleanup_registry();
		return CU_get_error();
	}

	if ((NULL == CU_add_test(pS, "Test für: get_hash()", test_hashing))){
		CU_cleanup_registry();
		return CU_get_error();
	}

	CU_basic_set_mode(CU_BRM_VERBOSE);
	CU_basic_run_tests();
	printf("\n");
	CU_basic_show_failures(CU_get_failure_list());
	printf("\n\n");
	CU_cleanup_registry();
	return CU_get_error();
}
