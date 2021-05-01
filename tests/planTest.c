//
// Created by Daniel Bill on 29.09.2020.
//



#include <sqlite3.h>
#include <stdio.h>

int main() {
    sqlite3 *db;
    int rc;
    char *zDbName = "test.db";
    int queries_size = 6;
    char* queries[] = {
        "EXPLAIN QUERY PLAN Select stt.jmeno, prt.jmeno, ste.rok, ste.body FROM student stt JOIN studuje ste on stt.sID = ste.sID JOIN predmet prt on ste.pID = prt.pID where ste.rok = 2010",
        "EXPLAIN QUERY PLAN SELECT a1.id, a1.groupby, a1.fkb, a1.search, a1.padding FROM A a1 JOIN B ON a1.fkb = B.id WHERE a1.search = 1 AND B.search = 1",
        "EXPLAIN QUERY PLAN SELECT a1.id, a1.groupby, a1.fkb, a1.search, (SELECT a2.padding FROM A a2 WHERE a1.id = a2.id) padding FROM A a1 JOIN B ON a1.fkb = B.id WHERE a1.search = 1 AND B.search = 1",
        "EXPLAIN QUERY PLAN SELECT B.groupby,COUNT(CASE WHEN A.search = 1 THEN 1 END) AS search1,COUNT(CASE WHEN A.search = 10 THEN 1 END) AS search2 FROM B LEFT JOIN A ON A.fkb = B.id WHERE B.search < 10 GROUP BY B.groupby",
        "EXPLAIN QUERY PLAN SELECT b1.id, b1.groupby, b1.search, b1.padding FROM B b1 WHERE EXISTS ( SELECT 1 FROM A WHERE b1.id = A.fkb AND A.groupby < 50 ) AND b1.search = 1",
        "EXPLAIN QUERY PLAN SELECT a1.id, a1.groupby, a1.fkb, a1.padding FROM A a1 JOIN ( SELECT groupby, MAX(search) search_max FROM A WHERE A.groupby < 50 GROUP BY groupby ) t2 ON a1.groupby = t2.groupby AND a1.search = t2.search_max"
    };
    printf("open connection\n");
    rc = sqlite3_open_v2(zDbName, &db, SQLITE_OPEN_READWRITE, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "sqlite3_open() returns %d\n", rc);
        return rc;
    }
    sqlite3_stmt *pStmt; 
    for (int i = 0; i < queries_size; i++) {
        rc = sqlite3_prepare_v2(db, queries[i], -1, &pStmt, NULL);
        if (rc != SQLITE_OK) {
            fprintf(stderr, "sqlite3_prepare_v2() returns %d\n", rc);
            return rc;
        }

        printf("\nresult:\n");
        while (SQLITE_ROW == sqlite3_step(pStmt)) {
            printf("%s \n", sqlite3_column_text(pStmt, 3));
        }
        sqlite3_finalize(pStmt);
    }
    sqlite3_close(db);
    printf("\nclose connection\n");
    return 0;
}
