//
// Created by Clarence Hirsch on 18/10/2023.
//

#include "inventory.h"
#include "../LOGGER/logger.h"
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
    if (inventory->size < inventory->max_size) {
        inventory->equipment[inventory->nbrEquipment] = equipment;
        inventory->nbrEquipment++;
        inventory->size++;
    }else{
        perror("Inventory is full");
    }
}

void addConsumableToInventory(Inventory *inventory, Consumable consumable) {
    if (inventory->size < inventory->max_size) {
        inventory->consumable[inventory->nbrConsumable] = consumable;
        inventory->nbrConsumable++;
        inventory->size++;
    }else{
        perror("Inventory is full");
    }
}

void removeConsumableFromInventory(Inventory *inventory, int index) {
    // Check if the index is valid
    if (index >= 0 && index < inventory->nbrConsumable) {

        // Shift all consumables after 'index' one position to the left
        for (int i = index; i < inventory->nbrConsumable - 1; i++) {
            inventory->consumable[i] = inventory->consumable[i + 1];
        }

        logMessage(INFO, "nbrConsumableBefore: %d", inventory->nbrConsumable);
        // Decrease the count of consumables
        inventory->nbrConsumable--;
        // Decrease the total size of the inventory
        inventory->size--;
        logMessage(INFO, "nbrConsumableAfter: %d", inventory->nbrConsumable);

        // Free the last item of the array
        //freeConsumable(&inventory->consumable[inventory->nbrConsumable]);
    } else {
        // Handle the case where the index is out of bounds
        logMessage(ERROR, "Error: Index %d is out of range for consumables.\n", index);
    }
}

void removeEquipmentFromInventory(Inventory *inventory, int index) {
    // Check if the index is valid
    if (index >= 0 && index < inventory->nbrEquipment) {

        // Shift all consumables after 'index' one position to the left
        for (int i = index; i < inventory->nbrEquipment - 1; i++) {
            inventory->equipment[i] = inventory->equipment[i + 1];
        }

        logMessage(INFO, "nbrConsumableBefore: %d", inventory->equipment);
        // Decrease the count of consumables
        inventory->nbrEquipment--;
        // Decrease the total size of the inventory
        inventory->size--;
        logMessage(INFO, "nbrConsumableAfter: %d", inventory->nbrEquipment);

        // Free the last item of the array
        //freeConsumable(&inventory->consumable[inventory->nbrConsumable]);
    } else {
        // Handle the case where the index is out of bounds
        logMessage(ERROR, "Error: Index %d is out of range for consumables.\n", index);
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



