//
// Created by Clarence Hirsch on 18/10/2023.
//

#ifndef DOOMDEPTHS_CONSUMABLE_H
#define DOOMDEPTHS_CONSUMABLE_H

enum consumableType {
    HEALING_POTION,
    MANA_POTION,
    BANDAGE,
    BUFF,
    ENEMY_DEBUFF
};

typedef struct Consumable {
    char *name;
    char *description;
    int price;
    int consumableEffectivenessValue;
    enum consumableType type;
} Consumable;

#endif //DOOMDEPTHS_CONSUMABLE_H
