//
// Created by Clarence Hirsch on 18/10/2023.
//

#ifndef DOOMDEPTHS_CONSUMABLE_H
#define DOOMDEPTHS_CONSUMABLE_H

#include "../MESSAGE_RESOLVER/messageResolver.h"

enum consumableType {
    HEALING,
    MANA_POTION,
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

Consumable *createRandomConsumableOfType(enum consumableType type);

Consumable *createRandomConsumable();

char * consumableToString(Consumable * consumable);

void printConsumable(Consumable * consumable);

Consumable *createConsumable(char *name,
                             char *description,
                             int price,
                             int consumableEffectivenessValue,
                             enum consumableType type);

char * shortConsumableToString(Consumable consumable, TranslationList * translationList);

void freeConsumable(Consumable * consumable);

#endif //DOOMDEPTHS_CONSUMABLE_H
