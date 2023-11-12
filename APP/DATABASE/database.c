//
// Created by Clarence Hirsch on 19/10/2023.
//

#include "database.h"
#include <stdio.h>
#include <stdlib.h>

int callback(void *NotUsed, int argc, char **argv, char **azColName)
{
    int i;
    for(i = 0; i<argc; i++)
    {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}


void createDatabase(sqlite3 *db, char *sql, char *zErrMsg, int* rc) {



    *rc = sqlite3_open("doomdepths.db", &db);

    if( rc )
    {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        exit(0);
    } else
    {
        printf("Database opened\n");
    }
}

void createTableEquipments(sqlite3 *db, char *sql, char *zErrMsg, int rc) {
    /* Create SQL statement */
    sql = "CREATE TABLE EQUIPMENTS("  \
         "ID INT PRIMARY KEY     NOT NULL," \
         "NAME           TEXT    NOT NULL," \
         "DESCRIPTION    TEXT    NOT NULL," \
         "EFFECTIVENESS  INT     NOT NULL," \
         "DURABILITY     INT     NOT NULL," \
         "DURABILITYMAX  INT     NOT NULL," \
         "PRICE          INT     NOT NULL," \
         "TYPE           INT     NOT NULL);";

    /* Execute SQL statement */
    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);

    if( rc != SQLITE_OK )
    {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else
    {
        fprintf(stdout, "Equipment table created successfully\n");
    }
}

void createTablePlayers(sqlite3 *db, char *sql, char *zErrMsg, int rc) {
    /* Create SQL statement */
    sql = "CREATE TABLE PLAYERS("  \
         "ID INT PRIMARY KEY     NOT NULL," \
         "NAME           TEXT    NOT NULL," \
         "health         INT     NOT NULL," \
         "maxHealth      INT     NOT NULL," \
         "attack         INT     NOT NULL," \
         "level          INT     NOT NULL," \
         "experience     INT     NOT NULL," \
         "gold          INT     NOT NULL," \
         "teamId         INT     NOT NULL);";



    /* Execute SQL statement */
    rc = sqlite3_exec(db, sql, NULL, 0, &zErrMsg);

    if( rc != SQLITE_OK )
    {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else
    {
        fprintf(stdout, "Table created successfully\n");
    }
}

void insterIntoTest(){
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    char *sql = malloc(sizeof(char)*500);

    /* Open database */
    rc = sqlite3_open("doomdepths.db", &db);

    if( rc )
    {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        exit(0);
    } else
    {
        fprintf(stderr, "Opened database successfully\n");
    }


    char buffer[500];
    sqlite3_snprintf(sizeof(buffer), buffer, "INSERT INTO OKOK(name, email) VALUES (%s, %s)", "tests", "test");
    rc = sqlite3_exec(db, buffer, 0, 0, &zErrMsg);


   /* *//* Create SQL statement *//*
    sql = "INSERT INTO test (id,name, email) VALUES (2, 'Paul', 'test@test.com' ); ";

    *//* Execute SQL statement *//*
    rc = sqlite3_exec(db, sql, 0, 0, &zErrMsg);
*/
    if( rc != SQLITE_OK )
    {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else
    {
        fprintf(stdout, "Records created successfully\n");
    }
    sqlite3_close(db);
}
