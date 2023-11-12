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

// Fonction pour lire un enregistrement Inventory
int readInventory(sqlite3 *db, Inventory *inventory) {
    const char *selectInventorySQL =
            "SELECT Inventory.id, "
            "Equipment.id AS equipment_id, Equipment.name AS equipment_name, Equipment.description AS equipment_description, "
            "Equipment.equipmentEffectivenessValue, Equipment.durability, Equipment.durabilityMax, Equipment.price, "
            "Consumable.id AS consumable_id, Consumable.name AS consumable_name, Consumable.description AS consumable_description, "
            "Consumable.price, Consumable.consumableEffectivenessValue, Consumable.type, "
            "Inventory.nbrEquipment, Inventory.nbrConsumable, Inventory.size, Inventory.max_size "
            "FROM Inventory "
            "JOIN Equipment ON Inventory.equipment_id = Equipment.id "
            "JOIN Consumable ON Inventory.consumable_id = Consumable.id "
            "WHERE Inventory.id = ?;";

    sqlite3_stmt *stmt;

    if (sqlite3_prepare_v2(db, selectInventorySQL, -1, &stmt, 0) == SQLITE_OK) {
        sqlite3_bind_int(stmt, 1, 1);

        if (sqlite3_step(stmt) == SQLITE_ROW) {
            inventory->id = sqlite3_column_int(stmt, 0);

            // Remplir la structure Equipment
            inventory->equipment->name = strdup((char *) sqlite3_column_text(stmt, 3));
            inventory->equipment->description = strdup((char *) sqlite3_column_text(stmt, 4));
            inventory->equipment->equipmentEffectivenessValue = sqlite3_column_int(stmt, 5);
            inventory->equipment->durability = sqlite3_column_int(stmt, 6);
            inventory->equipment->durabilityMax = sqlite3_column_int(stmt, 7);
            inventory->equipment->price = sqlite3_column_int(stmt, 8);

            // Remplir la structure Consumable
            inventory->consumable->name = strdup((char *) sqlite3_column_text(stmt, 10));
            inventory->consumable->description = strdup((char *) sqlite3_column_text(stmt, 11));
            inventory->consumable->price = sqlite3_column_int(stmt, 12);
            inventory->consumable->consumableEffectivenessValue = sqlite3_column_int(stmt, 13);
            inventory->consumable->type = sqlite3_column_int(stmt, 14);

            inventory->nbrEquipment = sqlite3_column_int(stmt, 15);
            inventory->nbrConsumable = sqlite3_column_int(stmt, 16);
            inventory->size = sqlite3_column_int(stmt, 17);
            inventory->max_size = sqlite3_column_int(stmt, 18);

            sqlite3_finalize(stmt);
            return 1; // Succès
        }
    }
}

// Fonction pour mettre à jour un enregistrement Inventory par son ID
int updateInventory(sqlite3 *db, const Inventory *inventory) {
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
        sqlite3_bind_int(stmt, 7, 1);

        if (sqlite3_step(stmt) == SQLITE_DONE) {
            sqlite3_finalize(stmt);
            return 1; // Succès
        }
    }

    sqlite3_finalize(stmt);
    return 0; // Échec
}