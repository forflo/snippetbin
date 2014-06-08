#include <stdio.h>
#include <string.h>
#include <sqlite3.h>
#include <stdlib.h>



int main(int argc, char *argv[]){
	int rc;
	sqlite3 *db;
	char *str;
	rc = sqlite3_open("bucket.db", &db);
	if(rc){
		printf("Fehler beim Öffnen\n");
		return EXIT_SUCCESS;
	}

	sqlite3_stmt *stmt;
	rc = sqlite3_prepare_v2(db, "select bin from bin_bucket where id = '7511cc9269c1f52e7ed31f0b0bfe742f';",-1 , &stmt, NULL);
	
	while ((rc = sqlite3_step(stmt)) != SQLITE_DONE){
		if (rc != SQLITE_ROW) {
			printf("Ein Fehler während des Steppens ist aufgetreten!");
			return EXIT_FAILURE;
		} else {
			printf("step\n");
			str = (char *) malloc(sqlite3_column_bytes(stmt, 0)+1);
			strcpy(str, (char *) sqlite3_column_blob(stmt, 0));
		}
	}

	printf("Data: %s\n", str);
	
}
