#include "player.h"
#include "../MESSAGE_RESOLVER/messageResolver.h"
#include <stdlib.h>
#include <stdio.h>
#include "string.h"
#include "../LOGGER/logger.h"

/**
 * Create a new player
 * <li>health : init at 100</li>
 * <li>max_health : init at 100</li>
 * <li>mana : init at 100</li>
 * <li>max_mana : init at 100</li>
 * <li>attack : init at 30</li>
 * <li>level : init at 0</li>
 * <li>experience : init at 0</li>
 * <li>experience_to_next_level : init at 200</li>
 * <li>gold : init at 0</li>
 * <li>x : init at 0</li>
 * <li>y : init at 0</li>
 * <li>weapon : init at default weapon</li>
 * <li>armor : init at default armor</li>
 * <li>inventory : init at 10</li>
 *
 * @param name
 * @return a default player
 */
Player * newPlayer(char * name, enum Language language){
    Player *player = malloc(sizeof(Player*));
    player->name = malloc(sizeof(char) * strlen(name));
    strcpy(player->name, name);
    player->health = 100;
    player->max_health = 100;
    player->mana = 100;
    player->max_mana = 100;
    player->attack = 30;
    player->level = 0;
    player->experience = 0;
    player->experience_to_next_level = 200;
    player->gold = 0;
    player->x = 0;
    player->y = 0;

    player->weapon = malloc(sizeof(Equipment*));
    player->armor = malloc(sizeof(Equipment*));
    Equipment * weapon = createDefaultWeapon();
    Equipment * armor = createDefaultArmor();
    player->weapon = weapon;
    player->armor = armor;

    Inventory * inventory = create_inventory(10);
    player->inventory = inventory;

    player->translationList = loadTranslations(languagePathResolver(language));


    return player;
}

void addEquipmentToPlayerInventory(Player * player, Equipment equipment){
    addEquipmentToInventory(player->inventory, equipment);
}

void addConsumableToPlayerInventory(Player * player, Consumable consumable){
    addConsumableToInventory(player->inventory, consumable);
}

void equipWeaponFromInventory(Player * player, int index){
    if (index < player->inventory->nbrEquipment){
        Equipment * tmp = player->weapon;
        player->weapon = &player->inventory->equipment[index];
        player->inventory->equipment[index] = *tmp;
    }else{
        perror("Index out of range");
    }
}

void equipNewWeapon(Player * player, Equipment * weapon){
    // add the new weapon to the inventory
    addEquipmentToPlayerInventory(player, *weapon);
    // equip the new weapon
    equipWeaponFromInventory(player, player->inventory->nbrEquipment-1);
}

void equipArmorFromInventory(Player * player, int index){
    if (index < player->inventory->nbrEquipment){
        Equipment * tmp = player->armor;
        player->armor = &player->inventory->equipment[index];
        player->inventory->equipment[index] = *tmp;
    }else{
        perror("Index out of range");
    }
}

void equipNewArmor(Player * player, Equipment * armor){
    // add the new armor to the inventory
    addEquipmentToPlayerInventory(player, *armor);
    // equip the new armor
    equipArmorFromInventory(player, player->inventory->nbrEquipment-1);
}

/**
 * Add gold to the player
 * @param player
 * @param gold
 */
void addGold(Player * player, int gold){
    player->gold += gold;
}

/**
 * Remove gold to the player
 * @param player
 * @param gold
 */
void removeGold(Player * player, int gold){
    player->gold -= gold;
}

/**
 * Add experience to the player
 * If the player has enough experience to level up, he will
 * The level up will increase his stats
 * The next level experience will be increased by 50%
 *
 * @param player the player to add experience to
 * @param experience the amount of experience to add
 */
void addExperience(Player * player, int experience){
    player->experience += experience;
    if (player->experience >= player->experience_to_next_level){
        player->level++;
        experience -= player->experience_to_next_level;
        player->experience_to_next_level *= 1.5;
        player->max_health += 10;
        player->health = player->max_health;
        player->max_mana += 10;
        player->mana = player->max_mana;
        player->attack += 5;
    }
}

void freePlayer(Player * player) {
    free(player->name);
    freeEquipment(player->weapon);
    freeEquipment(player->armor);
    freeInventory(player->inventory);
    freeTranslationList(player->translationList);
    free(player);
}



// print and toString of things related to player

char* weaponToString(Player * player) {
    equipmentToString(*player->weapon, player->translationList);
}

void printWeapon(Player * player) {
    printEquipment(*player->weapon, player->translationList);
}

char* armorToString(Player * player) {
    equipmentToString(*player->armor, player->translationList);
}

void printArmor(Player * player) {
    printEquipment(*player->armor, player->translationList);
}