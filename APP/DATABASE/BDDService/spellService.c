//
// Created by Neven Le Gall on 25/10/2023.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../sqlite3.h"

// Fonction pour créer un nouveau sort dans la table Spell
int createSpellbdd(sqlite3 *db, Spell *spell) {
    const char *insertSpellSQL =
            "INSERT INTO Spell (name, description, spellEffectivenessValue, type) "
            "VALUES (?, ?, ?, ?);";

    sqlite3_stmt *stmt;

    if (sqlite3_prepare_v2(db, insertSpellSQL, -1, &stmt, 0) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, spell->name, -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 2, spell->description, -1, SQLITE_STATIC);
        sqlite3_bind_int(stmt, 3, spell->spellEffectivenessValue);
        sqlite3_bind_int(stmt, 4, spell->type);

        int result = sqlite3_step(stmt);
        sqlite3_finalize(stmt);

        return (result == SQLITE_DONE) ? 1 : 0; // Succès si la requête est exécutée avec succès
    }

    return 0; // Échec
}

// Fonction pour lire un sort par son ID dans la table Spell
int readSpellbdd(sqlite3 *db, Spell *spell) {
    const char *selectSpellSQL =
            "SELECT * FROM Spell WHERE id = ?;";

    sqlite3_stmt *stmt;

    if (sqlite3_prepare_v2(db, selectSpellSQL, -1, &stmt, 0) == SQLITE_OK) {
        sqlite3_bind_int(stmt, 1, 1);

        if (sqlite3_step(stmt) == SQLITE_ROW) {
            spell->name = strdup((char *)sqlite3_column_text(stmt, 1));
            spell->description = strdup((char *)sqlite3_column_text(stmt, 2));
            spell->spellEffectivenessValue = sqlite3_column_int(stmt, 3);
            spell->type = sqlite3_column_int(stmt, 4);

            sqlite3_finalize(stmt);
            return 1; // Succès
        }
    }

    sqlite3_finalize(stmt);
    return 0; // Échec
}

// Fonction pour mettre à jour un sort dans la table Spell
int updateSpellbdd(sqlite3 *db, const Spell *spell) {
    const char *updateSpellSQL =
            "UPDATE Spell SET name = ?, description = ?, "
            "spellEffectivenessValue = ?, type = ? "
            "WHERE id = ?;";

    sqlite3_stmt *stmt;

    if (sqlite3_prepare_v2(db, updateSpellSQL, -1, &stmt, 0) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, spell->name, -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 2, spell->description, -1, SQLITE_STATIC);
        sqlite3_bind_int(stmt, 3, spell->spellEffectivenessValue);
        sqlite3_bind_int(stmt, 4, spell->type);
        sqlite3_bind_int(stmt, 5, 1);

        int result = sqlite3_step(stmt);
        sqlite3_finalize(stmt);

        return (result == SQLITE_DONE) ? 1 : 0; // Succès si la requête est exécutée avec succès
    }

    return 0; // Échec
}
