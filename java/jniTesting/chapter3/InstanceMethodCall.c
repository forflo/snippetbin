#include <jni.h>


JNIEXPORT void JNICALL Java_InstanceMethodCall_nativeMethod(JNIEnv *env, jobject obj){
	jclass cls = (*env)->GetObjectClass(env, obj);
	jmethodID mid = (*env)->GetMethodID(env, cls, "callback", "()V");
	if (mid ==NULL)
		return;
	printf("IN C:\n");
	(*env)->CallVoidMethod(env, obj, mid);
}
