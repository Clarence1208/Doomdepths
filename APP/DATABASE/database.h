//
// Created by Clarence Hirsch on 19/10/2023.
//

#ifndef DOOMDEPTHS_DATABASE_H
#define DOOMDEPTHS_DATABASE_H

#include "sqlite3.h"

void createDatabase(sqlite3 *db, char *sql, char *zErrMsg, int *rc);

void createTableEquipments(sqlite3 *db, char *sql, char *zErrMsg, int rc);

void insterIntoTest();

#endif //DOOMDEPTHS_DATABASE_H
