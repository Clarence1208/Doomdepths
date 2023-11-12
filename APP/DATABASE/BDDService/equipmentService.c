//
// Created by Neven Le Gall on 25/10/2023.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../sqlite3.h"

// Fonction pour créer un nouvel équipement dans la table Equipment
int createEquipment(const char *playerName, Equipment *equipment) {
    char filename[128];
    snprintf(filename, sizeof(filename), "%s.db", playerName); // Créer un nom de fichier basé sur le nom du joueur

    sqlite3 *db;

    int result = sqlite3_open(filename, &db);

    const char *insertEquipmentSQL =
            "INSERT INTO Equipment (id, name, description, equipmentEffectivenessValue, durability, durabilityMax, price) "
            "VALUES (?, ?, ?, ?, ?, ?);";

    sqlite3_stmt *stmt;

    if (sqlite3_prepare_v2(db, insertEquipmentSQL, -1, &stmt, 0) == SQLITE_OK) {
        sqlite3_bind_int(stmt, 0 , e)
        sqlite3_bind_text(stmt, 1, equipment->name, -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 2, equipment->description, -1, SQLITE_STATIC);
        sqlite3_bind_int(stmt, 3, equipment->equipmentEffectivenessValue);
        sqlite3_bind_int(stmt, 4, equipment->durability);
        sqlite3_bind_int(stmt, 5, equipment->durabilityMax);
        sqlite3_bind_int(stmt, 6, equipment->price);

        int result = sqlite3_step(stmt);
        sqlite3_finalize(stmt);
        sqlite3_close(db);

        return (result == SQLITE_DONE) ? 1 : 0; // Succès si la requête est exécutée avec succès
    }
    sqlite3_close(db);
    return 0; // Échec
}

// Fonction pour lire un équipement par son ID dans la table Equipment
int readEquipment(sqlite3 *db, Equipment *equipment) {
    const char *selectEquipmentSQL =
            "SELECT * FROM Equipment WHERE id = ?;";

    sqlite3_stmt *stmt;

    if (sqlite3_prepare_v2(db, selectEquipmentSQL, -1, &stmt, 0) == SQLITE_OK) {
        sqlite3_bind_int(stmt, 1, 1);

        if (sqlite3_step(stmt) == SQLITE_ROW) {
            equipment->name = strdup((char *)sqlite3_column_text(stmt, 1));
            equipment->description = strdup((char *)sqlite3_column_text(stmt, 2));
            equipment->equipmentEffectivenessValue = sqlite3_column_int(stmt, 3);
            equipment->durability = sqlite3_column_int(stmt, 4);
            equipment->durabilityMax = sqlite3_column_int(stmt, 5);
            equipment->price = sqlite3_column_int(stmt, 6);

            sqlite3_finalize(stmt);
            return 1; // Succès
        }
    }

    sqlite3_finalize(stmt);
    return 0; // Échec
}

// Fonction pour mettre à jour un équipement dans la table Equipment
int updateEquipment(sqlite3 *db, const Equipment *equipment) {
    const char *updateEquipmentSQL =
            "UPDATE Equipment SET name = ?, description = ?, "
            "equipmentEffectivenessValue = ?, durability = ?, durabilityMax = ?, price = ? "
            "WHERE id = ?;";

    sqlite3_stmt *stmt;

    if (sqlite3_prepare_v2(db, updateEquipmentSQL, -1, &stmt, 0) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, equipment->name, -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 2, equipment->description, -1, SQLITE_STATIC);
        sqlite3_bind_int(stmt, 3, equipment->equipmentEffectivenessValue);
        sqlite3_bind_int(stmt, 4, equipment->durability);
        sqlite3_bind_int(stmt, 5, equipment->durabilityMax);
        sqlite3_bind_int(stmt, 6, equipment->price);
        sqlite3_bind_int(stmt, 7, 1);

        int result = sqlite3_step(stmt);
        sqlite3_finalize(stmt);

        return (result == SQLITE_DONE) ? 1 : 0; // Succès si la requête est exécutée avec succès
    }

    return 0; // Échec
}
