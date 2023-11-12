//
// Created by Neven Le Gall on 25/10/2023.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../sqlite3.h"

// Fonction pour créer un nouveau consommable dans la table Consumable
int createConsumablebdd(sqlite3 *db, Consumable *consumable) {
    const char *insertConsumableSQL =
            "INSERT INTO Consumable (name, description, price, consumableEffectivenessValue, type) "
            "VALUES (?, ?, ?, ?, ?);";

    sqlite3_stmt *stmt;

    if (sqlite3_prepare_v2(db, insertConsumableSQL, -1, &stmt, 0) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, consumable->name, -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 2, consumable->description, -1, SQLITE_STATIC);
        sqlite3_bind_int(stmt, 3, consumable->price);
        sqlite3_bind_int(stmt, 4, consumable->consumableEffectivenessValue);
        sqlite3_bind_int(stmt, 5, consumable->type);

        int result = sqlite3_step(stmt);
        sqlite3_finalize(stmt);

        return (result == SQLITE_DONE) ? 1 : 0; // Succès si la requête est exécutée avec succès
    }

    return 0; // Échec
}

// Fonction pour lire un consommable par son ID dans la table Consumable
int readConsumablebdd(sqlite3 *db, Consumable *consumable) {
    const char *selectConsumableSQL =
            "SELECT * FROM Consumable WHERE id = ?;";

    sqlite3_stmt *stmt;

    if (sqlite3_prepare_v2(db, selectConsumableSQL, -1, &stmt, 0) == SQLITE_OK) {
        sqlite3_bind_int(stmt, 1, 1);

        if (sqlite3_step(stmt) == SQLITE_ROW) {
            consumable->name = strdup((char *)sqlite3_column_text(stmt, 1));
            consumable->description = strdup((char *)sqlite3_column_text(stmt, 2));
            consumable->price = sqlite3_column_int(stmt, 3);
            consumable->consumableEffectivenessValue = sqlite3_column_int(stmt, 4);
            consumable->type = sqlite3_column_int(stmt, 5);

            sqlite3_finalize(stmt);
            return 1; // Succès
        }
    }

    sqlite3_finalize(stmt);
    return 0; // Échec
}

// Fonction pour mettre à jour un consommable dans la table Consumable
int updateConsumablebdd(sqlite3 *db, const Consumable *consumable) {
    const char *updateConsumableSQL =
            "UPDATE Consumable SET name = ?, description = ?, "
            "price = ?, consumableEffectivenessValue = ?, type = ? "
            "WHERE id = ?;";

    sqlite3_stmt *stmt;

    if (sqlite3_prepare_v2(db, updateConsumableSQL, -1, &stmt, 0) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, consumable->name, -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 2, consumable->description, -1, SQLITE_STATIC);
        sqlite3_bind_int(stmt, 3, consumable->price);
        sqlite3_bind_int(stmt, 4, consumable->consumableEffectivenessValue);
        sqlite3_bind_int(stmt, 5, consumable->type);
        sqlite3_bind_int(stmt, 6, 1);

        int result = sqlite3_step(stmt);
        sqlite3_finalize(stmt);

        return (result == SQLITE_DONE) ? 1 : 0; // Succès si la requête est exécutée avec succès
    }

    return 0; // Échec
}
