#include <jni.h>
#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SqliteBridge.h"

jobjectArray result;
jobjectArray attributes;
JNIEnv *envi;
int cnt;
int rows;

/*
 + This routine is used for calculating the count of tuples
 + of the result of the sql-statement
*/
static int call(void *NotUsed, int argc, char **argv, char **azColName){
	rows++;
	return 0;
}

/*
 + Here starts the conversion of the result of the given sql
 + statement to both, an single dimensional object (string) array
 + and a two dimensional object (string) array.
 + The equivalent Java- structure would be "String[]" and "String[][]
*/
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
		for(i = 0; i < argc; i++){
			jstring tmpstr3 = (*envi)->NewStringUTF(envi, azColName[i]);
			(*envi)->SetObjectArrayElement(envi, tmpStrArr1, i, tmpstr3);
		}
		attributes = tmpStrArr1;
	}

	(*envi)->SetObjectArrayElement(envi, result, cnt++, tmpStrArr);
	return 0;
}

static int callDML(void *NotUsed, int argc, char **argv, char **azColName){
	//do noting...
	return 0;
}

/*
 + JNI function for the spedial data manipulating sql statements
 + e.g. "insert into foo ..." or "create table fooBafooBar ..."
*/
JNIEXPORT void JNICALL Java_SqliteBridge_execSqlDML(JNIEnv *env, jobject obj, jstring sql, jstring path, jobject data){
	sqlite3 *db;
	char *zErrMsg;
	int rc;

	if (sql == NULL || path == NULL) {
		printf("[native wrapper] missing arguments !\n");
		return ; 
	}

	const char *str1 = (*env)->GetStringUTFChars(env, sql, NULL); /* sql-statement */
	const char *str2 = (*env)->GetStringUTFChars(env, path, NULL); /* path name */

	if (str1 == NULL || str2 == NULL){
		printf("[native wrapper] Malloc Error\n");
		return ;
	}

	rc = sqlite3_open(str2, &db);
	if(rc != SQLITE_OK) {
		printf("[native wrapper] Error while opening the database\n");
		sqlite3_close(db);
		return;
	}

	rc = sqlite3_exec(db, str1, callDML, 0, &zErrMsg);
	if(rc != SQLITE_OK){
		printf("[native wrapper] Error while executing the sql- statement\n");
		printf("\t[Error] %s\n\t[SQL] %s\n", zErrMsg, str1);

		jclass cls = (*env)->GetObjectClass(env, data);
		if(cls == NULL){
			printf("[native wrapper] Malloc error !\n");
			return;
		}
		jfieldID fid = (*env)->GetFieldID(env, cls, "errors", "Ljava/lang/String;");
		if(fid == NULL){
			printf("[native wrapper] Malloc error \n");
			return ;
		}
	
		jstring tmp = (*env)->NewStringUTF(env, zErrMsg);	
		(*env)->SetObjectField(env, data, fid, tmp);
		sqlite3_free(zErrMsg);
	}

	sqlite3_close(db);
	return;
}

/*
 + native implementation of the native declared method "execSql"
 + which resides in the SqliteBridge.java file ...
*/
JNIEXPORT void JNICALL Java_SqliteBridge_execSql(JNIEnv *env, jobject obj, jstring sql, jstring path, jobject data){
	rows = 0;
	cnt = 0;
	attributes = NULL;
	result = NULL;
	envi = env;
	sqlite3 *db;
	char *zErrMsg;
	int rc;

	if (sql == NULL || path ==NULL){
		printf("missing arguments\n");
		return;
	}
	/*
	 + transform the java-string into
	 + c-compatible char arrays 
	 + by using the GetStringUTFChars()
	 + function...
	*/
	const char *str1 = (*env)->GetStringUTFChars(env, sql, NULL); /* str1 is the sql statement */
	const char *str2 = (*env)->GetStringUTFChars(env, path, NULL); /* str2 is the pathname */
	
	if (str1 == NULL || str2 == NULL)
		return; /* OutOfMemoryError already thrown. Immediate stop is required !  */

	/* 	open the database ...	*/
	rc = sqlite3_open(str2, &db);
	if(rc){
		printf("[native wrapper] Error while opening the database\n");
		sqlite3_close(db);
		return;
	}

	rc = sqlite3_exec(db, str1, call, 0, &zErrMsg);
	if(rc != SQLITE_OK){
		printf("[native wrapper] Error while computing the count of tuples\n");
		printf("\t[Error] %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
		/*	
		 * okay failure while calculating the number of tuplse ...
		 * now set the attribute of the DbData object to "SQLERROR"
		 */
		jclass cls = (*env)->GetObjectClass(env, data);
		if (cls == NULL) 
			return;
		jfieldID fid = (*env)->GetFieldID(env, cls, "errors", "Ljava/lang/String;");
		if (fid == NULL)
			return;
		jstring tmpStr = (*env)->NewStringUTF(env, zErrMsg);
		(*env)->SetObjectField(env, data, fid, tmpStr);
		printf("[native wrapper] The Error string has been set in the DbData Object ...");
		return;
	}

	/* 
	 + the sql statement first goes in the sqlite3_exec function above. Furhter
	 + checks are unnecessary ...
	 */
	rc = sqlite3_exec(db, str1, callback, 0, &zErrMsg);
	//if(rc != SQLITE_OK){
	//	printf("[native warapper] Error while executing the sql- statement\n");
	//	printf("\t[Error] %s\n\t[SQL-Statement] %s\n", zErrMsg, str1);
	//	sqlite3_free(zErrMsg);
	//}
	
	/*
	 + Here begins the creation of an "DbData" object
	 + which is used to easy use the resulting data
	 + in an java program. If the sql statement was 
	 + successful, but did not produce any data,
	 + the Object will be NULL
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

	sqlite3_close(db);
	return;
}



JNIEXPORT void JNICALL Java_SqliteBridge_createDatabase(JNIEnv *env, jobject obj, jstring path){
	/* Umwandlung der Java-Datenstrukutr String in eine c verträgliche Form*/
	sqlite3 *db;
	int rc;
	
	const char *p = (*env)->GetStringUTFChars(env, path, NULL);
	if (p == NULL)
		return; /* OutOfMemoryError already thrown. Immediate stop is required !  */

	rc = sqlite3_open(p, &db);
	if (rc){
		printf("[native wrapper] Error while creating the database\n");
		sqlite3_close(db);
		return;
	}

	sqlite3_close(db);
}
