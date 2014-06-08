#include <jni.h>
#include <stdio.h>
#include "InstanceFieldAccess.h"

JNIEXPORT void JNICALL Java_InstanceFieldAccess_accessField(JNIEnv *env, jobject obj){
	jfieldID fid;
	jstring jstr;
	const char *str;
	jclass cls = (*env)->GetObjectClass(env, obj);
	printf("In C: \n");
	fid = (*env)->GetFieldID(env, cls, "s", "Ljava/lang/String;");

	if(fid ==NULL)
		return ;
	jstr = (*env)->GetObjectField(env, obj, fid);
	str = (*env)->GetStringUTFChars(env, jstr, NULL);
	if(str ==NULL)
		return ;
	printf(" c.s = \"%s\"\n", str);	
	jstr = (*env)->NewStringUTF(env, "AAAAAAAAAAAAAAA123");
	if(jstr ==NULL)
		return ;
	(*env)->SetObjectField(env, obj, fid, jstr);
}
