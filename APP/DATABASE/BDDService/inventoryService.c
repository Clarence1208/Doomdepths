//
// Created by Neven Le Gall on 25/10/2023.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../sqlite3.h"

#include "../../INVENTORY/inventory.h"

// Fonction pour créer un nouvel enregistrement Inventory
int createInventory(sqlite3 *db, const Inventory *inventory) {
    const char *insertInventorySQL = "INSERT INTO Inventory (equipment, consumable, nbrEquipment, nbrConsumable, size, max_size) VALUES (?, ?, ?, ?, ?, ?);";
    sqlite3_stmt *stmt;

    if (sqlite3_prepare_v2(db, insertInventorySQL, -1, &stmt, 0) == SQLITE_OK) {
        // Bind les valeurs de la structure Inventory aux paramètres de la requête SQL
        sqlite3_bind_blob(stmt, 1, inventory->equipment, sizeof(Equipment) * inventory->nbrEquipment, SQLITE_STATIC);
        sqlite3_bind_blob(stmt, 2, inventory->consumable, sizeof(Consumable) * inventory->nbrConsumable, SQLITE_STATIC);
        sqlite3_bind_int(stmt, 3, inventory->nbrEquipment);
        sqlite3_bind_int(stmt, 4, inventory->nbrConsumable);
        sqlite3_bind_int(stmt, 5, inventory->size);
        sqlite3_bind_int(stmt, 6, inventory->max_size);

        if (sqlite3_step(stmt) == SQLITE_DONE) {
            sqlite3_finalize(stmt);
            return 1; // Succès
        }
    }

    sqlite3_finalize(stmt);
    return 0; // Échec
}

// Fonction pour lire un enregistrement Inventory par son ID
int readInventory(sqlite3 *db, int inventoryId, Inventory *inventory) {
    const char *selectInventorySQL = "SELECT * FROM Inventory WHERE id = ?;";
    sqlite3_stmt *stmt;

    if (sqlite3_prepare_v2(db, selectInventorySQL, -1, &stmt, 0) == SQLITE_OK) {
        sqlite3_bind_int(stmt, 1, 1);

        if (sqlite3_step(stmt) == SQLITE_ROW) {
            inventory->id = sqlite3_column_int(stmt, 0);
            // Récupérer les données binaires (equipment et consumable) et les autres champs ici
            // Assurez-vous de dé-sérialiser les données correctement

            sqlite3_finalize(stmt);
            return 1; // Succès
        }
    }

    sqlite3_finalize(stmt);
    return 0; // Échec
}

// Fonction pour mettre à jour un enregistrement Inventory par son ID
int updateInventory(sqlite3 *db, int inventoryId, const Inventory *inventory) {
    const char *updateInventorySQL = "UPDATE Inventory SET equipment = ?, consumable = ?, nbrEquipment = ?, nbrConsumable = ?, size = ?, max_size = ? WHERE id = ?;";
    sqlite3_stmt *stmt;

    if (sqlite3_prepare_v2(db, updateInventorySQL, -1, &stmt, 0) == SQLITE_OK) {
        // Bind les valeurs de la structure Inventory aux paramètres de la requête SQL
        sqlite3_bind_blob(stmt, 1, inventory->equipment, sizeof(Equipment) * inventory->nbrEquipment, SQLITE_STATIC);
        sqlite3_bind_blob(stmt, 2, inventory->consumable, sizeof(Consumable) * inventory->nbrConsumable, SQLITE_STATIC);
        sqlite3_bind_int(stmt, 3, inventory->nbrEquipment);
        sqlite3_bind_int(stmt, 4, inventory->nbrConsumable);
        sqlite3_bind_int(stmt, 5, inventory->size);
        sqlite3_bind_int(stmt, 6, inventory->max_size);
        sqlite3_bind_int(stmt, 7, inventoryId);

        if (sqlite3_step(stmt) == SQLITE_DONE) {
            sqlite3_finalize(stmt);
            return 1; // Succès
        }
    }

    sqlite3_finalize(stmt);
    return 0; // Échec
}