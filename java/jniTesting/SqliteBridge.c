#include <jni.h>
#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SqliteBridge.h"

jobjectArray result = NULL;
jobjectArray attributes = NULL ;
JNIEnv *envi;
int cnt = 0;
int rows = 0;

static int call(void *NotUsed, int argc, char **argv, char **azColName){
	rows++;
	return 0;
}

static int callback(void *NotUsed, int argc, char **argv, char **azColName){
	jclass jstrtmp = (*envi)->FindClass(envi, "Ljava/lang/String;");
	if ( jstrtmp == NULL )
		return;
	jobjectArray tmpStrArr = (*envi)->NewObjectArray(envi, argc, jstrtmp, NULL);
	if ( tmpStrArr == NULL )
		return;
	int i;
	for(i = 0; i < argc; i++){
		jstring newString;
		if ( argv[i] )
			newString = (*envi)->NewStringUTF(envi, argv[i]);
		else
			newString = (*envi)->NewStringUTF(envi, "null");

		if(newString == NULL)
			return;
		(*envi)->SetObjectArrayElement(envi, tmpStrArr, i, newString);
	}

	if ( result == NULL) {
		jclass jstr = (*envi)->FindClass(envi, "[Ljava/lang/String;");
		if (jstr == NULL)
			return;
		result = (*envi)->NewObjectArray(envi, rows, jstr, NULL); 
		if(result == NULL)
			return;
	}
	
	if ( attributes == NULL){
		jclass jstrtmp2 = (*envi)->FindClass(envi, "Ljava/lang/String;");
		if ( jstrtmp2 == NULL )
			return;
		jobjectArray tmpStrArr1 = (*envi)->NewObjectArray(envi, argc, jstrtmp2, NULL);
		if ( tmpStrArr1 == NULL )
			return;
		for(i = 0; i< argc; i++){
			jstring tmpstr3 = (*envi)->NewStringUTF(envi, azColName[i]);
			(*envi)->SetObjectArrayElement(envi, tmpStrArr1, i, tmpstr3);
		}
		attributes = tmpStrArr1;
	}

	(*envi)->SetObjectArrayElement(envi, result, cnt++, tmpStrArr);
	return 0;
}

JNIEXPORT void JNICALL Java_SqliteBridge_execSql(JNIEnv *env, jobject obj, jstring sql, jstring path, jobject data){
	envi = env;
	sqlite3 *db;
	char *zErrMsg = 0;
	int rc;

	if (sql == NULL || path ==NULL){
		printf("missing arguments\n");
		return;
	}
	/*
		transform the java-string into
		c-compatible char arrays 
		by using the GetStringUTFChars()
		function...
	*/
	const char *str1 = (*env)->GetStringUTFChars(env, sql, NULL); /* str1 is the sql statement */
	const char *str2 = (*env)->GetStringUTFChars(env, path, NULL);
	
	if (str1 == NULL || str2 == NULL)
		return; /* OutOfMemoryError already thrown. Immediate stop is required !  */

	rc = sqlite3_open(str2, &db);
	if(rc){
		printf("Error in one\n");
		sqlite3_close(db);
		return;
	}
	rc = sqlite3_exec(db, str1, call, 0, &zErrMsg);
	if(rc != SQLITE_OK){
		printf("Error in three\n");
		sqlite3_free(zErrMsg);
	}

	rc = sqlite3_exec(db, str1, callback, 0, &zErrMsg);
	if(rc != SQLITE_OK){
		printf("Error in two\n");
		sqlite3_free(zErrMsg);
	}
	
	/*
		Here begins the creation of an "DbData" object
		which is used to easy use the resulting data
		in an java program. If the sql statement was 
		successful, but did not produce any data,
		the Object will be NULL
	*/
	jclass cls = (*env)->GetObjectClass(env, data);
	if (cls ==NULL )
		return;
	jfieldID fid = (*env)->GetFieldID(env, cls, "attributes", "[Ljava/lang/String;");
	if (fid == NULL)
		return ;
	(*env)->SetObjectField(env, data, fid, attributes);
	fid = (*env)->GetFieldID(env, cls, "data", "[[Ljava/lang/String;");
	if (fid == NULL)
		return;
	
	(*env)->SetObjectField(env, data, fid, result);

	return;
}
