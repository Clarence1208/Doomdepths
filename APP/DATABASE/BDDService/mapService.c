//
// Created by Neven Le Gall on 25/10/2023.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../sqlite3.h"

// Insérer la salle dans la table Room
const char *insertRoomSQL =
        "INSERT INTO Room (type, x, y) VALUES (?, ?, ?);";

sqlite3_stmt *stmt;

if (sqlite3_prepare_v2(db, insertRoomSQL, -1, &stmt, 0) == SQLITE_OK) {
sqlite3_bind_text(stmt, 1, &roomType, 1, SQLITE_STATIC);
sqlite3_bind_int(stmt, 2, i); // i est la coordonnée x de la salle
sqlite3_bind_int(stmt, 3, j); // j est la coordonnée y de la salle

sqlite3_step(stmt);
sqlite3_finalize(stmt);
}

// Structure pour stocker les informations d'une salle
typedef struct {
    char type;
    int x;
    int y;
} RoomInfo;

// Fonction pour récupérer la carte depuis la base de données
void retrieveMap(sqlite3 *db, char **map) {
    const char *selectRoomsSQL =
            "SELECT type, x, y FROM Room;";

    sqlite3_stmt *stmt;

    if (sqlite3_prepare_v2(db, selectRoomsSQL, -1, &stmt, 0) == SQLITE_OK) {
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            char roomType = (char)sqlite3_column_text(stmt, 0)[0];
            int x = sqlite3_column_int(stmt, 1);
            int y = sqlite3_column_int(stmt, 2);

            // Utilisez les informations pour mettre à jour votre carte
            map[x][y] = roomType;
        }
    }

    sqlite3_finalize(stmt);
}