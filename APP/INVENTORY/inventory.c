//
// Created by Clarence Hirsch on 18/10/2023.
//

#include "inventory.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

Inventory *create_inventory(int max_size) {
    Inventory *inventory = malloc(sizeof(Inventory));
    Equipment *equipment = malloc(sizeof(Equipment) * max_size);
    Consumable *consumable = malloc(sizeof(Consumable) * max_size);
    inventory->equipment = equipment;
    inventory->consumable = consumable;
    inventory->nbrEquipment = 0;
    inventory->nbrConsumable = 0;
    inventory->size = 0;
    inventory->max_size = max_size;
    return inventory;
}

char * inventoryToString(Inventory * inventory, TranslationList * translationList) {
    char * string = malloc(sizeof(char) * 500);
    char * tmp = malloc(sizeof(char) * 100);
    sprintf(string, "Inventory :    %d/%d\n", inventory->size, inventory->max_size);
    for (int i = 0; i < inventory->nbrEquipment; ++i) {
        sprintf(tmp, "%d - %s\n", i, translate(inventory->equipment[i].name, translationList));
        strcat(string ,tmp);
        strcpy(tmp, "");
    }
    for (int i = 0; i < inventory->nbrConsumable; ++i) {
        sprintf(tmp, "%d - %s\n", i + inventory->nbrEquipment, translate(inventory->consumable[i].name, translationList));
        strcat(string ,tmp);
        strcpy(tmp, "");
    }
    for (int i = inventory->size; i < inventory->max_size ; i ++){
        sprintf(tmp, "%d - %s\n", i, translate("emptySlot", translationList));
        strcat(string ,tmp);
        strcpy(tmp, "");
    }
    free(tmp);

    return string;
}

void printInventory(Inventory * inventory, TranslationList * translationList) {
    char * string = inventoryToString(inventory, translationList);
    printf("%s", string);
    free(string);
}

char * inventoryItemToString(Inventory * inventory, int slotNbr, TranslationList * translationList) {
    char * string = malloc(sizeof(char) * 100);

    if (slotNbr > inventory->size) {
        sprintf(string, "%d - %s", slotNbr, translate("emptySlot", translationList));
    } else if (slotNbr < inventory->nbrEquipment) {
        sprintf(string, "%d - %s", slotNbr, translate(inventory->equipment[slotNbr].name, translationList));
    } else {
        sprintf(string, "%d - %s", slotNbr, translate(inventory->consumable[slotNbr - inventory->nbrEquipment].name, translationList));
    }

    return string;
}

int isSlotEquipment (Inventory * inventory, int slotNbr) {
    return slotNbr < inventory->nbrEquipment;
}

int isSlotWeapon (Inventory * inventory, int slotNbr) {
    return isSlotEquipment(inventory, slotNbr) && inventory->equipment[slotNbr].type == WEAPON;
}

void printInventoryItem(Inventory * inventory, int slotNbr, TranslationList * translationList) {
    char * string = inventoryItemToString(inventory, slotNbr, translationList);
    printf("%s", string);
    free(string);
}

void addEquipmentToInventory(Inventory *inventory, Equipment equipment) {
    if (inventory->size < inventory->max_size - 1) {
        inventory->equipment[inventory->size] = equipment;
        inventory->nbrEquipment++;
        inventory->size++;
    }else{
        perror("Inventory is full");
    }
}

void addConsumableToInventory(Inventory *inventory, Consumable consumable) {
    if (inventory->size < inventory->max_size - 1) {
        inventory->consumable[inventory->size] = consumable;
        inventory->nbrConsumable++;
        inventory->size++;
    }else{
        perror("Inventory is full");
    }
}

void freeInventory(Inventory *inventory) {
    for (int i = 0; i < inventory->nbrEquipment; ++i) {
        freeEquipment(&inventory->equipment[i]);
    }
    for (int i = 0; i < inventory->nbrConsumable; ++i) {
        freeConsumable(&inventory->consumable[i]);
    }
    free(inventory->equipment);
    free(inventory->consumable);
    free(inventory);
}



