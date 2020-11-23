//
// Created by Daniel Bill on 29.09.2020.
//



#include <sqlite3.h>
#include <stdio.h>


int main() {
    sqlite3 *db;
    int rc;
    char *zDbName = "C:/Users/bil0104/Desktop/test.db";
    printf("open connection\n");
    rc = sqlite3_open_v2(zDbName, &db, SQLITE_OPEN_READWRITE, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "sqlite3_open() returns %d\n", rc);
        return rc;
    }
    sqlite3_stmt *pStmt;
    // jake predmety studenti studoval v roce 2010
    /*
    * EXPLAIN QUERY:
    QUERY PLAN
    |--SCAN TABLE studuje AS ste
    |--SEARCH TABLE student AS stt USING INDEX sqlite_autoindex_student_1 (sID=?)
    `--SEARCH TABLE predmet AS prt USING INDEX sqlite_autoindex_predmet_1 (pID=?)
    */
    rc = sqlite3_prepare_v2(db,
                            "EXPLAIN QUERY PLAN Select stt.jmeno, prt.jmeno, ste.rok, ste.body "
                            "FROM student stt "
                            "JOIN studuje ste on stt.sID = ste.sID "
                            "JOIN predmet prt on ste.pID = prt.pID "
                            "where ste.rok = 2010",
                            -1, &pStmt, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "sqlite3_prepare_v2() returns %d\n", rc);
        return rc;
    }

    printf("\nresult:\n");
    while (SQLITE_ROW == sqlite3_step(pStmt)) {
        printf("%s \n", sqlite3_column_text(pStmt, 3));
    }
    sqlite3_finalize(pStmt);
    sqlite3_close(db);
    printf("\nclose connection\n");
    return 0;
}
