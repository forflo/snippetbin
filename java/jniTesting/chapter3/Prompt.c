#include <string.h>
#include <stdio.h>
#include <jni.h>
#include "Prompt.h"

JNIEXPORT jstring JNICALL Java_Prompt_getLine(JNIEnv *env, jobject o, jstring p){
	char buf[128];
	const jbyte *str;
	//es ginge auch 
	//const char *str;
	str = (*env)->GetStringUTFChars(env, p, NULL);
	if (str == NULL)
		return NULL;
	printf("%s", str);
	(*env)->ReleaseStringUTFChars(env, p, str);
	scanf("%s", buf);
	return (*env)->NewStringUTF(env, buf);
}
