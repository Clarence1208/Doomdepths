//
// Created by Neven Le Gall on 25/10/2023.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../sqlite3.h"

// Fonction pour créer un nouveau monstre dans la table Monster
int createMonsterbdd(sqlite3 *db, Monster *monster) {
    const char *insertMonsterSQL =
            "INSERT INTO Monster (name, hp, attack, defense, speed, level, type) "
            "VALUES (?, ?, ?, ?, ?, ?, ?);";

    sqlite3_stmt *stmt;

    if (sqlite3_prepare_v2(db, insertMonsterSQL, -1, &stmt, 0) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, monster->name, -1, SQLITE_STATIC);
        sqlite3_bind_int(stmt, 2, monster->hp);
        sqlite3_bind_int(stmt, 3, monster->attack);
        sqlite3_bind_int(stmt, 4, monster->defense);
        sqlite3_bind_int(stmt, 5, monster->level);
        sqlite3_bind_int(stmt, 6, monster->experience);
        sqlite3_bind_int(stmt, 7, monster->type);

        int result = sqlite3_step(stmt);
        sqlite3_finalize(stmt);

        return (result == SQLITE_DONE) ? 1 : 0; // Succès si la requête est exécutée avec succès
    }

    return 0; // Échec
}

// Fonction pour lire un monstre par son ID dans la table Monster
int readMonsterbdd(sqlite3 *db, Monster *monster) {
    const char *selectMonsterSQL =
            "SELECT * FROM Monster WHERE id = ?;";

    sqlite3_stmt *stmt;

    if (sqlite3_prepare_v2(db, selectMonsterSQL, -1, &stmt, 0) == SQLITE_OK) {
        sqlite3_bind_int(stmt, 1, 1);

        if (sqlite3_step(stmt) == SQLITE_ROW) {
            monster->name = strdup((char *)sqlite3_column_text(stmt, 1));
            monster->hp = sqlite3_column_int(stmt, 2);
            monster->attack = sqlite3_column_int(stmt, 3);
            monster->defense = sqlite3_column_int(stmt, 4);
            monster->level = sqlite3_column_int(stmt, 5);
            monster->experience = sqlite3_column_int(stmt, 6);
            monster->type = sqlite3_column_int(stmt, 7);

            sqlite3_finalize(stmt);
            return 1; // Succès
        }
    }

    sqlite3_finalize(stmt);
    return 0; // Échec
}

// Fonction pour mettre à jour un monstre dans la table Monster
int updateMonsterbdd(sqlite3 *db, const Monster *monster) {
    const char *updateMonsterSQL =
            "UPDATE Monster SET name = ?, hp = ?, attack = ?, defense = ?, speed = ?, level = ?, type = ? "
            "WHERE name = ?;";

    sqlite3_stmt *stmt;

    if (sqlite3_prepare_v2(db, updateMonsterSQL, -1, &stmt, 0) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, monster->name, -1, SQLITE_STATIC);
        sqlite3_bind_int(stmt, 2, monster->hp);
        sqlite3_bind_int(stmt, 3, monster->attack);
        sqlite3_bind_int(stmt, 4, monster->defense);
        sqlite3_bind_int(stmt, 5, monster->level);
        sqlite3_bind_int(stmt, 6, monster->experience);
        sqlite3_bind_int(stmt, 7, monster->type);
        sqlite3_bind_int(stmt, 8, 1);

        int result = sqlite3_step(stmt);
        sqlite3_finalize(stmt);

        return (result == SQLITE_DONE) ? 1 : 0; // Succès si la requête est exécutée avec succès
    }

    return 0; // Échec
}
