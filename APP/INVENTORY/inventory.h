//
// Created by Clarence Hirsch on 18/10/2023.
//

#ifndef DOOMDEPTHS_INVENTORY_H
#define DOOMDEPTHS_INVENTORY_H

#include "../EQUIPMENT/equipment.h"
#include "../CONSUMABLE/consumable.h"

typedef struct Inventory {
    Equipment *equipment;
    Consumable *consumable;
    int nbrEquipment;
    int nbrConsumable;
    int size;
    int max_size;
} Inventory;

Inventory *create_inventory(int max_size);

char * inventoryToString(Inventory * inventory, TranslationList * translationList);

void printInventory(Inventory * inventory, TranslationList * translationList);

void addEquipmentToInventory(Inventory *inventory, Equipment equipment);

void addConsumableToInventory(Inventory *inventory, Consumable consumable);

void freeInventory(Inventory *inventory);

#endif //DOOMDEPTHS_INVENTORY_H
