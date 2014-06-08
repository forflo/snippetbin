#include <stdio.h>
#include "call.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sqlite3.h>
#include "hashing.h"

static int callback(void *NotUsed, int argc, char **argv, char **azColName){
}

/* Datenbankanbindung */
sqlite3 *db;
char *zErrMsg;

int open_db(char *path);
int setup_db(char *path);
int write_bin(char *str);
int update_bin(char *id);
int read_bin(char *id);
int drop_bin(char *id);
int get_bin(char *id);
int is_added(char *str);

int open_db(char *path){
	int rc = sqlite3_open(path, &db);
	if(rc){
		printf("Fehler beim öffnen der Datenbank!");
		sqlite3_close(db);
		return 1;
	}
	return 0;
}

/* writes a new binary */
int add(const char *name, const char *blob, const char *code){
	char *hash = get_hash(str);
	char stmt[130] = "";
}

int drop(const char *name){

}

int get_blob(char *name){
	char stmt[130] = "select id from bin_bucket where name = '";
	strcat(stmt, name); strcat(stmt, "';");
	
	sqlite3_stmt *comp_stmt;
	int rc = sqlite3_prepare(db, stmt, -1, &comp_stmt, NULL);
	if(rc){ printf("read_bin: SQL_Fehler!\n"); return 1; }
	
	while ((rc = sqlite3_step(comp_stmt)) != SQLITE_DONE){
		if (rc != SQLITE_ROW) return 1;
		else printf
	}
}

int update_bin(char *id){
	
}

/*
takes a binary stream, converts it to md5 and checks if there is any
entry in the list.
0 if there is a entry
1 if it is not
*/
int is_added(char *str){
	char *hash = get_hash(str);
	char stmt[130] = "select id from bin_bucket where id = ";
	strcat(stmt, hash);
	strcat(stmt, ";");
	sqlite3_stmt *comp_st;
	int rc = sqlite3_prepare(db, stmt, -1, &comp_st, NULL);
	if (rc != SQLITE_OK){
		printf("[is_added] SQL_Fehler!\n");
		return 1;
	}
	
	if (count_rows(stmt) == 0) return 0;
	else return 1;
}

int setup_db(char *path){
	char *err;
	int rc = sqlite3_exec(db, "create table bin_bucket (id text not null, bin blob not null, name text not null, code text not null, primary key(id));", NULL, 0, &err);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "Ein SQL-Error ist aufgetreten!\n");
		fprintf("stderr", "Nachricht: %s\n", err);
		return 1;
	} else return 0;
}

int count_rows(sqlite3_stmt *stmt){
        int count=0, rc;
        while ((rc = sqlite3_step(stmt)) != SQLITE_DONE){
                if (rc == SQLITE_ROW) count ++;
                else return -1;
        }
        return count;
}
