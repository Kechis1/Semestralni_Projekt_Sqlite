//
// Created by Daniel Bill on 29.09.2020.
//



#include <sqlite3.h>
#include <stdio.h>


int main() {
    sqlite3 *db;
    int rc;
    char *zDbName = "/Users/danielbill/sqlite/databases/users.db";
    printf("open connection\n");
    rc = sqlite3_open_v2(zDbName, &db, SQLITE_OPEN_READWRITE, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "sqlite3_open() returns %d\n", rc);
        return rc;
    }
    sqlite3_stmt *pStmt;
    // jake predmety studenti studoval v roce 2010
    rc = sqlite3_prepare_v2(db,
                            "SELECT * FROM users WHERE name = 'Maria';",
                            -1, &pStmt, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "sqlite3_prepare_v2() returns %d\n", rc);
        return rc;
    }

    printf("\nresult:\n");
    while (SQLITE_ROW == sqlite3_step(pStmt)) {
        printf("%s | %s | %i | %i \n", sqlite3_column_text(pStmt, 0), sqlite3_column_text(pStmt, 1),
               sqlite3_column_int(pStmt, 2),
               sqlite3_column_int(pStmt, 3));
    }

    sqlite3_finalize(pStmt);
    sqlite3_close(db);
    printf("\nclose connection");
    return 0;
}
