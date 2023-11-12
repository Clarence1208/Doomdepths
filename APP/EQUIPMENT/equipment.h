//
// Created by Clarence Hirsch on 18/10/2023.
//

#ifndef DOOMDEPTHS_EQUIPMENT_H
#define DOOMDEPTHS_EQUIPMENT_H

#include "../MESSAGE_RESOLVER/messageResolver.h"

/*
 * Enumeration of the different types of equipment
 * -WEAPON: weapon (sword, axe, ...)
 * -ARMOR: armor (helmet, chestplate, ...)
 */
enum EquipmentType {
    WEAPON,
    ARMOR
};

/**
 * Structure of an equipment
 *  -name: name of the equipment
 *  -equipmentEffectivenessValue: value that represent the effectiveness of the equipment
 *         depending on the type of the equipment.
 *         (for a weapon, it will be the damage, for an armor, it will be the defense)
 *  -durability: durability of the equipment
 *  -durabilityMax: maximum durability of the equipment
 *  -price: price of the equipment for the shop
 *  -type: type of the equipment (weapon or armor)
 *
 */
typedef struct Equipment {
    char *name;
    char *description;
    int equipmentEffectivenessValue;
    int durability;
    int durabilityMax;
    int price;
    int nbAttack;
    enum EquipmentType type;
} Equipment;

Equipment *createDefaultWeapon();

Equipment *createDefaultArmor();

Equipment *createEquipment(char *name, char *description, int equipmentEffectivenessValue, int durability, int durabilityMax, int price, int nbAttack, enum EquipmentType type);

char *equipmentToString(Equipment equipment, TranslationList *translationList);

void printEquipment(Equipment equipment, TranslationList *translationList);

void freeEquipment(Equipment *equipment);

#endif //DOOMDEPTHS_EQUIPMENT_H
