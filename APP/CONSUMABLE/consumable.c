//
// Created by Clarence Hirsch on 18/10/2023.
//

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include "consumable.h"

Consumable *createConsumable(char *name, char *description, int price, int consumableEffectivenessValue, enum consumableType type) {
    Consumable *consumable = malloc(sizeof(Consumable));
    consumable->name = malloc(sizeof(char) * strlen(name));
    strcpy(consumable->name, name);
    consumable->description = malloc(sizeof(char) * strlen(description));
    strcpy(consumable->description, description);
    consumable->price = price;
    consumable->consumableEffectivenessValue = consumableEffectivenessValue;
    consumable->type = type;

    return consumable;
}

Consumable *createRandomConsumableOfType(enum consumableType type) {
    Consumable *consumable = malloc(sizeof(Consumable));
    // init rand seed
    srand(time(NULL));
    int price = rand() % 100;
    int consumableEffectivenessValue = rand() % 100;
    int typeInt = rand() % 5;
    switch (typeInt) {
        case 1:
            createConsumable("Healing Potion", "Heals 50 HP", price, consumableEffectivenessValue, HEALING_POTION);
            break;
        case 2:
            createConsumable("Mana Potion", "Restores 50 MP", price, consumableEffectivenessValue, MANA_POTION);
            break;
        case 3:
            createConsumable("Bandage", "Heals 25 HP", price, consumableEffectivenessValue, BANDAGE);
            break;
        case 4:
            createConsumable("Buff", "Increases attack by 10", price, consumableEffectivenessValue, BUFF);
            break;
        case 5:
            createConsumable("Enemy Debuff", "Decreases enemy attack by 10", price, consumableEffectivenessValue, ENEMY_DEBUFF);
            break;
    }
    return consumable;
}


char * consumableToString(Consumable * consumable) {
    char * string = malloc(sizeof(char) * 500);
    char * tmp = malloc(sizeof(char) * 100);
    sprintf(string, "Consumable : %s\n", consumable->name);
    sprintf(tmp, "Description : %s\n", consumable->description);
    strcat(string ,tmp);
    sprintf(tmp, "Price : %d\n", consumable->price);
    strcat(string ,tmp);
    sprintf(tmp, "Consumable Effectiveness Value : %d\n", consumable->consumableEffectivenessValue);
    strcat(string ,tmp);
    sprintf(tmp, "Type : %d\n", consumable->type);
    strcat(string ,tmp);
    free(tmp);

    return string;
}

void printConsumable(Consumable * consumable) {
    char * string = consumableToString(consumable);
    printf("%s", string);
    free(string);
}

void freeConsumable(Consumable * consumable) {
    free(consumable->name);
    free(consumable->description);
    free(consumable);
}