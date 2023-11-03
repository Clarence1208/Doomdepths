//
// Created by Clarence Hirsch on 18/10/2023.
//

#ifndef DOOMDEPTHS_PLAYER_H
#define DOOMDEPTHS_PLAYER_H

#import "../EQUIPMENT/equipment.h"
#import "../SPELL/spells.h"
#import "../INVENTORY/inventory.h"

typedef struct Player {
    char *name;
    int health;
    int max_health;
    int mana;
    int max_mana;
    int attack;
    int level;
    int experience;
    int gold;
    int x;
    int y;
    Equipment *weapon;
    Equipment *armor;
    Spells *spells;
    Inventory *inventory;
}Player;


#endif //DOOMDEPTHS_PLAYER_H
