//
// Created by Clarence Hirsch on 18/10/2023.
//

#include "equipment.h"
#include "../MESSAGE_RESOLVER/messageResolver.h"
#include <stdlib.h>
#include <stdio.h>

Equipment *createDefaultWeapon() {
    Equipment *weapon = malloc(sizeof(Equipment));
    weapon->name = "basicSword";
    weapon->description = "basicSwordDescription";
    weapon->equipmentEffectivenessValue =  50;
    weapon->durability = 100;
    weapon->durabilityMax = 100;
    weapon->price = 0;
    weapon->type = WEAPON;
    return weapon;
}

Equipment *createDefaultArmor() {
    Equipment *armor = malloc(sizeof(Equipment));
    armor->name = "basicArmor";
    armor->description = "basicArmorDescription";
    armor->equipmentEffectivenessValue =  50;
    armor->durability = 100;
    armor->durabilityMax = 100;
    armor->price = 0;
    armor->type = ARMOR;
    return armor;
}

Equipment *createEquipment(char *name, char *description, int equipmentEffectivenessValue, int durability, int durabilityMax, int price, enum EquipmentType type) {
    Equipment *equipment = malloc(sizeof(Equipment));
    equipment->name = name;
    equipment->description = description;
    equipment->equipmentEffectivenessValue = equipmentEffectivenessValue;
    equipment->durability = durability;
    equipment->durabilityMax = durabilityMax;
    equipment->price = price;
    equipment->type = type;
    return equipment;
}

char *equipmentToString(Equipment equipment, TranslationList *translationList) {
    char *equipmentString = malloc(sizeof(char) * 256);
    sprintf(equipmentString, "Name: %s\nDescription: %s\nEquipmentEffectivenessValue: %d\nDurability: %d\nDurabilityMax: %d\nPrice: %d\nType: %d\n", translate(equipment.name, translationList), translate(equipment.description, translationList), equipment.equipmentEffectivenessValue, equipment.durability, equipment.durabilityMax, equipment.price, equipment.type);
    return equipmentString;
}

void printEquipment(Equipment equipment, TranslationList *translationList) {
    char *equipmentString = equipmentToString(equipment, translationList);
    printf("%s", equipmentString);
    free(equipmentString);
}

void freeEquipment(Equipment *equipment) {
    free(equipment->name);
    free(equipment->description);
    free(equipment);
}