//
// Created by Clarence Hirsch on 12/11/2023.
//

#include "shop.h"
#include "../PLAYER/player.h"
#include "../UTILS/utils.h"
#include "../EQUIPMENT/equipment.h"
#include "../MESSAGE_RESOLVER/messageResolver.h"
#include "../LOGGER/logger.h"
#include "../INVENTORY/inventoryMenu.h"


Equipment **createEquipmentsForSale(Player *player) {
    Equipment **equipments = malloc(sizeof(Equipment*) * 4);
    int durability = player->weapon->durabilityMax;
    int equipmentEffectivenessValue = player->weapon->equipmentEffectivenessValue;

    //random between 0 and 1
    int random = rand() % 2;
    if (random == 0) {
        equipments[0] = createEquipment("basicSword", "basicSwordDescription", equipmentEffectivenessValue * 1.2, durability * 1.2, durability * 1.2, 10 * (player->map_level / 2), WEAPON);
        equipments[1] = createEquipment("LegendarySword", "LegendarySwordDescription", equipmentEffectivenessValue * 2, durability * 2, durability * 2, 10 * (player->map_level), WEAPON);
        equipments[2] = createEquipment("basicShield", "basicShieldDescription", equipmentEffectivenessValue * 1.2, durability * 1.2, durability * 1.2, 10 * (player->map_level / 2), ARMOR);
        equipments[3] = createEquipment("advancedShield", "advancedShieldDescription", equipmentEffectivenessValue * 1.5, durability * 1.5, durability * 1.5, 10 * (player->map_level), ARMOR);
    } else {
       equipments[0] = createEquipment("basicSword", "basicSwordDescription", equipmentEffectivenessValue * 1.2, durability * 1.2, durability * 1.2, 10 * (player->map_level / 2), WEAPON);
       equipments[1] = createEquipment("advancedWeapon", "advancedWeaponDescription", equipmentEffectivenessValue * 1.5, durability * 1.5, durability * 1.5, 10 * (player->map_level), WEAPON);
       equipments[2] = createEquipment("basicShield", "basicShieldDescription", equipmentEffectivenessValue * 1.2, durability * 1.2, durability * 1.2, 10 * (player->map_level / 2), ARMOR);
       equipments[3] = createEquipment("LegendaryShield", "LegendaryShieldDescription", equipmentEffectivenessValue * 2, durability * 2, durability * 2, 10 * (player->map_level), ARMOR);
    }
    return equipments;
}

Consumable **createConsumablesForSale(Player *player) {
    Consumable **consumables = malloc(sizeof(Consumable*) * 2);
    int durability = player->weapon->durabilityMax;
    int equipmentEffectivenessValue = player->weapon->equipmentEffectivenessValue;

    //random between 0 and 1
    int random = rand() % 2;
    if (random == 0) {
        consumables[0] = createConsumable("basicPotion", "basicPotionDescription", 10 * (player->map_level / 2), (int) player->max_health / 4, HEALING);
        consumables[1] = createConsumable("advancedManaPotion", "advancedManaPotionDescription", 10 * (player->map_level), (int) player->max_mana / 2, MANA_POTION);
    } else {
        consumables[0] = createConsumable("basicManaPotion", "basicManaPotionDescription", 10 * (player->map_level / 2), (int) player->max_mana / 4, MANA_POTION);
        consumables[1] = createConsumable("advancedPotion", "advancedPotionDescription", 10 * (player->map_level), (int) player->max_health / 2, HEALING);
    }

    return consumables;
}


void enterShop(Player * player) {

    Equipment **equipments = createEquipmentsForSale(player);
    Consumable **consumables = createConsumablesForSale(player);

    int choice = 0;
    int movement = 0;

    do {
        system("/bin/stty cooked");
        cls();
        // "Welcome to the shop, what do you want  ?"
        printf("%s", translate("shopWelcome", player->translationList));
        printf("\n\n");
        // "1. Equipment:"
        printf("%s\n", translate("shopEquipment", player->translationList));
        for (int i = 0; i < 4; i++) {
           if (choice == i){
                printf("\033[1;34m(*) -- %s\033[0m\n", shortEquipmentToString(*equipments[i], player->translationList));
              } else {
                printf("() -- %s\n", shortEquipmentToString(*equipments[i], player->translationList));
           }
        }
        printf("\n");
        // "2. Consumable:"
        printf("%s\n", translate("shopConsumable", player->translationList));
        for (int i = 0; i < 2; i++) {
            if (choice == i + 4){
                printf("\033[1;34m(*) -- %s\033[0m\n", shortConsumableToString(*consumables[i], player->translationList));
            } else {
                printf("() -- %s\n", shortConsumableToString(*consumables[i], player->translationList));
            }
        }

        printf("\n");
        // "Press b to buy, p to leave"
        printf("%s\n", translate("shopBuyOrLeave", player->translationList));
        // "You can only buy one item in the shop"
        printf("%s\n", translate("shopOnlyOneItem", player->translationList));
        system("/bin/stty raw");
        movement = getchar();
        system("/bin/stty cooked");

        if (movement == 66 && choice < 5) {
            choice++;
        }
        if (movement == 65 && choice > 0) {
            choice--;
        }
        if (movement == 'b' || movement == 'B') {
            if (choice < 4) {
                if (player->gold < equipments[choice]->price) {
                    logMessage(INFO, "Player tried to buy an equipment but didn't have enough gold");
                    cls();
                    printf("%s\n", translate("shopNotEnoughGold", player->translationList));
                    printf("\n");
                    printf("%s\n", translate("pressAnyKey", player->translationList));
                    system("/bin/stty raw");
                    getchar();
                    system("/bin/stty cooked");
                    movement = 0;
                }else {
                    int result = addEquipmentToPlayerInventoryMenu(player, *equipments[choice]);
                    if (result == 0) {
                        movement = 0;
                    }else{
                        cls();
                        printf("%s\n", translate("shopBoughtEquipment", player->translationList));
                        printf("\n");
                        printf("%s\n", translate("pressAnyKey", player->translationList));
                        system("/bin/stty raw");
                        getchar();
                        system("/bin/stty cooked");
                    }
                }
            } else {
                if (player->gold < consumables[choice - 4]->price) {
                    logMessage(INFO, "Player tried to buy a consumable but didn't have enough gold");
                    cls();
                    printf("%s\n", translate("shopNotEnoughGold", player->translationList));
                    printf("\n");
                    printf("%s\n", translate("pressAnyKey", player->translationList));
                    system("/bin/stty raw");
                    getchar();
                    system("/bin/stty cooked");
                    movement = 0;
                }else {
                    int result = addConsumableToPlayerInventoryMenu(player, *consumables[choice - 4]);
                    if (result == 0) {
                        movement = 0;
                    }else{
                        cls();
                        printf("%s\n", translate("shopBoughtConsumable", player->translationList));
                        printf("\n");
                        printf("%s\n", translate("pressAnyKey", player->translationList));
                        system("/bin/stty raw");
                        getchar();
                        system("/bin/stty cooked");
                    }
                }
            }
        }
    } while (movement != 'p' && movement != 'P' && movement != 'b' && movement != 'B');

    if (movement == 'p' || movement == 'P') {
        free(equipments);
        free(consumables);
        logMessage(INFO, "Player left the shop without buying anything");
        return;
    }
}
