#include <stdio.h>
#include <jni.h>
#include <stdlib.h>
#include "IntArray.h"

JNIEXPORT jint JNICALL Java_IntArray_sumArray(JNIEnv *env, jobject a, jintArray arr){
	jint *iarr;
	jint i, sum = 0;
	iarr = (*env)->GetIntArrayElements(env, arr, NULL);
	if ( iarr == NULL )
		return 0;
	for(i = 0; i < 10; i++){
		sum += iarr[i];
		printf("%i,  ", iarr[i]);
	}
	(*env)->ReleaseIntArrayElements(env, arr, iarr, 0);	
	return sum;
}
