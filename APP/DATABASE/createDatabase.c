//
// Created by Neven Le Gall on 25/10/2023.
//

#include "database.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <io.h>

int createTables(sqlite3 *db);

int createDatabase(const char *playerName, char **dbName) {
    char filename[128];
    snprintf(filename, sizeof(filename), "%s.db", playerName); // Créer un nom de fichier basé sur le nom du joueur

    sqlite3 *db;

    int result = sqlite3_open(filename, &db);

    if (result == SQLITE_OK) {
        createTables(db); // Créer les tables dans la base de données
        printf("Base de donnees creee avec succes : %s\n", filename);
        sqlite3_close(db);
        *dbName = strdup(filename); // Copie du nom de la base de données pour une utilisation ultérieure
        return 1; // Succès
    } else {
        printf("Erreur lors de la creation de la base de donnees : %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 0; // Échec
    }
}

int doesDatabaseExist(const char *dbName) {
    printf("Verification de l'existence de la base de donnees : %s\n", dbName);
    //Prend dbname et rajoute .db à la fin
    char filename[128];
    snprintf(filename, sizeof(filename), "%s.db", dbName);
    if (access(filename, F_OK) != -1) {
        // Le fichier (base de données) existe
        printf("La base de donnees existe deja : %s\n", filename);
        return 1;
    } else {
        // Le fichier (base de données) n'existe pas
        printf("La base de donnees n'existe pas : %s\n", filename);
        return 0;
    }
}

// Fonction pour créer les tables dans la base de données
int createTables(sqlite3 *db) {
    // Création de la table "Player"
    const char *createPlayerTableSQL =
            "CREATE TABLE IF NOT EXISTS Player ("
            "id INTEGER PRIMARY KEY AUTOINCREMENT,"
            "name TEXT NOT NULL,"
            "health INTEGER NOT NULL,"
            "max_health INTEGER NOT NULL,"
            "mana INTEGER NOT NULL,"
            "max_mana INTEGER NOT NULL,"
            "attack INTEGER NOT NULL,"
            "level INTEGER NOT NULL,"
            "experience INTEGER NOT NULL,"
            "experience_to_next_level INTEGER NOT NULL,"
            "gold INTEGER NOT NULL,"
            "x INTEGER NOT NULL,"
            "y INTEGER NOT NULL"
            ");";
    int result = sqlite3_exec(db, createPlayerTableSQL, 0, 0, 0);

    // Création de la table "Inventory"
    const char *createInventoryTableSQL =
            "CREATE TABLE IF NOT EXISTS Inventory ("
            "id INTEGER PRIMARY KEY AUTOINCREMENT,"
            "equipment INTEGER,"
            "consumable INTEGER,"
            "nbrEquipment INTEGER NOT NULL,"
            "nbrConsumable INTEGER NOT NULL,"
            "size INTEGER NOT NULL,"
            "max_size INTEGER NOT NULL,"
            "FOREIGN KEY(id) REFERENCES Player(id)"
            ");";
    result = sqlite3_exec(db, createInventoryTableSQL, 0, 0, 0);

    // Création de la table "Equipment"
    const char *createEquipmentTableSQL =
            "CREATE TABLE IF NOT EXISTS Equipment ("
            "id INTEGER PRIMARY KEY AUTOINCREMENT,"
            "name TEXT NOT NULL,"
            "description TEXT,"
            "equipmentEffectivenessValue INTEGER NOT NULL,"
            "durability INTEGER NOT NULL,"
            "durabilityMax INTEGER NOT NULL,"
            "price INTEGER NOT NULL,"
            "type INTEGER NOT NULL,"
            "player_id INTEGER,"
            "inventory_id INTEGER,"
            "FOREIGN KEY(player_id) REFERENCES Player(id),"
            "FOREIGN KEY(inventory_id) REFERENCES Inventory(id)"
            ");";
    result = sqlite3_exec(db, createEquipmentTableSQL, 0, 0, 0);

    // Création de la table "Consumable"
    const char *createConsumableTableSQL =
            "CREATE TABLE IF NOT EXISTS Consumable ("
            "id INTEGER PRIMARY KEY AUTOINCREMENT,"
            "name TEXT NOT NULL,"
            "description TEXT,"
            "price INTEGER NOT NULL,"
            "consumableEffectivenessValue INTEGER NOT NULL,"
            "type INTEGER NOT NULL,"
            "inventory_id INTEGER,"
            "FOREIGN KEY(inventory_id) REFERENCES Inventory(id)"
            ");";
    result = sqlite3_exec(db, createConsumableTableSQL, 0, 0, 0);

    // Création de la table "Spell"
    const char *createSpellTableSQL =
            "CREATE TABLE IF NOT EXISTS Spell ("
            "id INTEGER PRIMARY KEY AUTOINCREMENT,"
            "name TEXT NOT NULL,"
            "description TEXT,"
            "spellEffectivenessValue INTEGER NOT NULL,"
            "type INTEGER NOT NULL,"
            "player_id INTEGER,"
            "FOREIGN KEY(player_id) REFERENCES Player(id)"
            ");";
    result = sqlite3_exec(db, createSpellTableSQL, 0, 0, 0);

    // Création de la table "Spells"
    const char *createSpellsTableSQL =
            "CREATE TABLE IF NOT EXISTS Spells ("
            "id INTEGER PRIMARY KEY AUTOINCREMENT,"
            "player_id INTEGER NOT NULL,"
            "size INTEGER NOT NULL,"
            "max_size INTEGER NOT NULL,"
            "FOREIGN KEY(player_id) REFERENCES Player(id)"
            ");";
    result = sqlite3_exec(db, createSpellsTableSQL, 0, 0, 0);

    // Création de la table "Monster"
    const char *createMonsterTableSQL =
            "CREATE TABLE IF NOT EXISTS Monster ("
            "id INTEGER PRIMARY KEY AUTOINCREMENT,"
            "name TEXT NOT NULL,"
            "hp INTEGER NOT NULL,"
            "attack INTEGER NOT NULL,"
            "defense INTEGER NOT NULL,"
            "level INTEGER NOT NULL,"
            "experience INTEGER NOT NULL,"
            "type INTEGER NOT NULL"
            ");";
    result = sqlite3_exec(db, createMonsterTableSQL, 0, 0, 0);

    if (result != SQLITE_OK) {
        fprintf(stderr, "Erreur lors de la création des tables : %s\n", sqlite3_errmsg(db));
        return 0; // Échec
    }

    return 1; // Succès
}
