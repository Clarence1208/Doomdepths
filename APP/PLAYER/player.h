//
// Created by Clarence Hirsch on 18/10/2023.
//

#ifndef DOOMDEPTHS_PLAYER_H
#define DOOMDEPTHS_PLAYER_H

#include "../EQUIPMENT/equipment.h"
#include "../SPELL/spells.h"
#include "../INVENTORY/inventory.h"

typedef struct Player {
    char *name;
    int health;
    int max_health;
    int mana;
    int max_mana;
    int attack;
    int level;
    int experience;
    int experience_to_next_level;
    int gold;
    int x;
    int y;
    Equipment *weapon;
    Equipment *armor;
    Spells *spells;
    Inventory *inventory;
    TranslationList *translationList;
}Player;

Player * newPlayer(char * name, enum Language language);

void addExperience(Player * player, int experience);

void freePlayer(Player * player);


char* weaponToString(Player * player);

void printWeapon(Player * player);

char* armorToString(Player * player);

void printArmor(Player * player);


#endif //DOOMDEPTHS_PLAYER_H
