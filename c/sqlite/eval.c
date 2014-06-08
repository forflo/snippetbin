#include <sqlite3.h>
#include <string.h>
#include <stdio.h>

int count_rows(sqlite3_stmt *stmt);

int main(void){
	sqlite3 *db;
	char *err;	
	int rc = sqlite3_open("bucket.db", &db);
	if(rc){
		printf("Fehler!\n");
		sqlite3_close(db);
		return 1;
	}
	char st[] = "select * from bin_bucket where id = 123;";
	sqlite3_stmt *stmt;
	
	rc = sqlite3_prepare_v2(db, st, -1, &stmt, NULL);
	if (rc != SQLITE_OK){
		printf("SQL-Fehler!\n");
		sqlite3_close(db);
		return 1;
	}
	
	

		
	while( (rc = sqlite3_step(stmt)) != SQLITE_DONE){
		if (rc != SQLITE_ROW){
			printf("Step-Fehler\n");
			sqlite3_close(db);
			return 1;
		} else {
			printf("Neue Zeile:\n");
			int i;
			for (i=0; i<sqlite3_column_count(stmt); i++){
				printf("|%s|", sqlite3_column_text(stmt, i ));
			}
			printf("\n");
		}
	}
	rc = sqlite3_prepare_v2(db, st, -1, &stmt, NULL);
	printf("Anzahl der Ergebniszeilen: %d\n", count_rows(stmt));
	sqlite3_close(db);
	return 0;
}

int count_rows(sqlite3_stmt *stmt){
	int count=0, rc;
	while ((rc = sqlite3_step(stmt)) != SQLITE_DONE){
		if (rc == SQLITE_ROW) count ++;
		else return -1;
	}
	return count;
}
