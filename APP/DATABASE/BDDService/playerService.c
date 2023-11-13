//
// Created by Neven Le Gall on 25/10/2023.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../sqlite3.h"

#include "../../PLAYER/player.h"

// Fonction pour créer un nouvel enregistrement Player
int createPlayer(const Player *player) {
    const char *insertPlayerSQL = "INSERT INTO Player (name, health, max_health, mana, max_mana, attack, level, experience, experience_to_next_level, gold, x, y) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?);";
    sqlite3_stmt *stmt;

    snprintf(filename, sizeof(filename), "%s.db", player->name); // Créer un nom de fichier basé sur le nom du joueur

    sqlite3 *db;

    int result = sqlite3_open(filename, &db);

    if (sqlite3_prepare_v2(db, insertPlayerSQL, -1, &stmt, 0) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, player->name, -1, SQLITE_STATIC);
        sqlite3_bind_int(stmt, 2, player->health);
        sqlite3_bind_int(stmt, 3, player->max_health);
        sqlite3_bind_int(stmt, 4, player->mana);
        sqlite3_bind_int(stmt, 5, player->max_mana);
        sqlite3_bind_int(stmt, 6, player->attack);
        sqlite3_bind_int(stmt, 7, player->level);
        sqlite3_bind_int(stmt, 8, player->map_level);
        sqlite3_bind_int(stmt, 9, player->experience);
        sqlite3_bind_int(stmt, 10, player->experience_to_next_level);
        sqlite3_bind_int(stmt, 11, player->gold);
        sqlite3_bind_int(stmt, 12, player->x);
        sqlite3_bind_int(stmt, 13, player->y);

        if (sqlite3_step(stmt) == SQLITE_DONE) {
            sqlite3_finalize(stmt);
            sqlite3_close(db);
            return 1; // Succès
        }
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return 0; // Échec
}

// Fonction pour lire un enregistrement Player
int readPlayer(char *name, Player *player) {
    const char *selectPlayerSQL = "SELECT * FROM Player WHERE id = ?;";
    sqlite3_stmt *stmt;
    snprintf(filename, sizeof(filename), "%s.db", name); // Créer un nom de fichier basé sur le nom du joueur

    sqlite3 *db;

    int result = sqlite3_open(filename, &db);

    if (sqlite3_prepare_v2(db, selectPlayerSQL, -1, &stmt, 0) == SQLITE_OK) {
        sqlite3_bind_int(stmt, 1, 1);

        if (sqlite3_step(stmt) == SQLITE_ROW) {
            player->name = strdup((const char *)sqlite3_column_text(stmt, 1));
            player->health = sqlite3_column_int(stmt, 2);
            player->max_health = sqlite3_column_int(stmt, 3);
            player->mana = sqlite3_column_int(stmt, 4);
            player->max_mana = sqlite3_column_int(stmt, 5);
            player->attack = sqlite3_column_int(stmt, 6);
            player->level = sqlite3_column_int(stmt, 7);
            player->map_level = sqlite3_column_int(stmt, 8);
            player->experience = sqlite3_column_int(stmt, 9);
            player->experience_to_next_level = sqlite3_column_int(stmt, 10);
            player->gold = sqlite3_column_int(stmt, 11);
            player->x = sqlite3_column_int(stmt, 12);
            player->y = sqlite3_column_int(stmt, 13);

            sqlite3_finalize(stmt);
            sqlite3_close(db);
            return 1; // Succès
        }
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return 0; // Échec
}

// Fonction pour mettre à jour un enregistrement Player
int updatePlayer(const Player *player) {
    const char *updatePlayerSQL = "UPDATE Player SET name = ?, health = ?, max_health = ?, mana = ?, max_mana = ?, attack = ?, level = ?, experience = ?, experience_to_next_level = ?, gold = ?, x = ?, y = ? WHERE id = ?;";
    sqlite3_stmt *stmt;

    if (sqlite3_prepare_v2(db, updatePlayerSQL, -1, &stmt, 0) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, player->name, -1, SQLITE_STATIC);
        sqlite3_bind_int(stmt, 2, player->health);
        sqlite3_bind_int(stmt, 3, player->max_health);
        sqlite3_bind_int(stmt, 4, player->mana);
        sqlite3_bind_int(stmt, 5, player->max_mana);
        sqlite3_bind_int(stmt, 6, player->attack);
        sqlite3_bind_int(stmt, 7, player->level);
        sqlite3_bind_int(stmt, 8, player->experience);
        sqlite3_bind_int(stmt, 9, player->experience_to_next_level);
        sqlite3_bind_int(stmt, 10, player->gold);
        sqlite3_bind_int(stmt, 11, player->x);
        sqlite3_bind_int(stmt, 12, player->y);
        sqlite3_bind_int(stmt, 13, 1);

        if (sqlite3_step(stmt) == SQLITE_DONE) {
            sqlite3_finalize(stmt);
            return 1; // Succès
        }
    }

    sqlite3_finalize(stmt);
    return 0; // Échec
}