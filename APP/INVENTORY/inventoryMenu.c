//
// Created by Clarence Hirsch on 05/11/2023.
//

#include <stdio.h>
#include <stdlib.h>
#include "inventoryMenu.h"
#include "inventory.h"
#include "../UTILS/utils.h"
#include "../PLAYER/player.h"
#include "../LOGGER/logger.h"

void printSelectionItemInventoryMenu (Inventory * inventory, int selectedItem, TranslationList * translationList) {
    for (int i = 0; i < inventory->size; ++i) {
        if (i == selectedItem) {
            printf("\x1b[30;47m");
            printf("(X)");
        } else {
            printf("()");
        }
        printInventoryItem(inventory, i, translationList);
        if (i == selectedItem) {
            printf("\x1b[0m");
        }
        printf("\n");
    }
    for (int i = inventory->size; i < inventory->max_size; ++i) {
        printf("-- %d - %s\n", i, translate("emptySlot", translationList));
    }
}
void selectableItemInventoryMenu (Player * player) {
    int slotNbr = 0;
    char movement = 0;

    do {
        system("/bin/stty cooked");
        cls();
        printf("%s est equipé en armure\n", translate(player->weapon->name, player->translationList));
        printf("%s est equipé en arme\n", translate(player->armor->name, player->translationList));
        printf("\nSelect an item : \n");
        printSelectionItemInventoryMenu(player->inventory, slotNbr, player->translationList);
        printf("\nPress c to use selected item\n");
        printf("Press p to quit\n");
//        printf("movement : %d\n", movement);
        system("/bin/stty raw");
        //echap char to quit
        movement = getchar();
        system("/bin/stty cooked");
        if (movement == 66 && slotNbr < player->inventory->size - 1 || movement =='s') {
            slotNbr++;
        } else if (movement == 65 && slotNbr > 0) {
            slotNbr--;
        }
        if (movement == 'c' || movement == 'C'){
            if (isSlotEquipment(player->inventory, slotNbr)) {
                if (isSlotWeapon(player->inventory, slotNbr)){
                    equipWeaponFromInventory(player, slotNbr);
                    logMessage(INFO, "weapon equipped : %s --- slotnbr %d", player->weapon->name, slotNbr);
                }else {
                    equipArmorFromInventory(player, slotNbr);
                }
            } else {
                useConsumableFromPlayerInventory(player, slotNbr- player->inventory->nbrEquipment);
            }
        }
    } while (movement != 'p' && movement != 'P');
}

void removeItemFromPlayerInventoryMenu(Player * player) {
    int slotNbr = 0;
    char movement = 0;

    do {
        system("/bin/stty cooked");
        cls();
        printf("%s est equipé en armure\n", translate(player->weapon->name, player->translationList));
        printf("%s est equipé en arme\n", translate(player->armor->name, player->translationList));
        printf("\nSelect an item to remove from player inventory : \n");
        printSelectionItemInventoryMenu(player->inventory, slotNbr, player->translationList);
        printf("\nPress c to confirm\n");
//        printf("movement : %d\n", movement);
        system("/bin/stty raw");
        //echap char to quit
        movement = getchar();
        system("/bin/stty cooked");
        if (movement == 66 && slotNbr < player->inventory->size - 1 || movement =='s') {
            slotNbr++;
        } else if (movement == 65 && slotNbr > 0) {
            slotNbr--;
        }
    } while (movement != 'c' && movement != 'C');

    if (isSlotEquipment(player->inventory, slotNbr)) {
        removeEquipmentFromInventory(player->inventory, slotNbr);
    } else {
        removeConsumableFromInventory(player->inventory, slotNbr- player->inventory->nbrEquipment);
    }
}


void addEquipmentToPlayerInventoryMenu(Player * player, Equipment equipment) {
    int selected = 0;
    int movement = 0;
    if (player->inventory->size < player->inventory->max_size) {
        do {
            system("/bin/stty cooked");
            cls();
            printf("\n\n Voulez-vous ajouter %s à votre inventaire ?\n", translate(equipment.name, player->translationList) );

            if (selected == 0) {
                printf("\x1b[30;47m(X) oui\x1b[0m\n");
                printf("() non\n");
            } else {
                printf("() oui\n");
                printf("\x1b[30;47m(X) non\x1b[0m\n");
            }
            printf("\nPress c to confirm\n");

            system("/bin/stty raw");
            movement = getchar();
            system("/bin/stty cooked");
            if (movement == 66 && selected < 1 || movement =='s') {
                selected++;
            } else if (movement == 65 && selected > 0) {
                selected--;
            }
        } while (movement != 'c' && movement != 'C');
    } else {
        do {
            system("/bin/stty cooked");
            cls();
            printf("\n\n L'inventaiter est plein, voulez-vous enlever un objet pour ajouter %s ?\n", translate(equipment.name, player->translationList) );

            if (selected == 0) {
                printf("\x1b[30;47m(X) oui\x1b[0m\n");
                printf("() non\n");
            } else {
                printf("() oui\n");
                printf("\x1b[30;47m(X) non\x1b[0m\n");
            }
            printf("\nPress c to confirm\n");

            system("/bin/stty raw");
            movement = getchar();
            system("/bin/stty cooked");
            if (movement == 66 && selected < 1 || movement =='s') {
                selected++;
            } else if (movement == 65 && selected > 0) {
                selected--;
            }
        } while (movement != 'c' && movement != 'C');

        if (selected == 0) {
            removeItemFromPlayerInventoryMenu(player);
        }
    }

    if (selected == 0) {
        addEquipmentToPlayerInventory(player, equipment);
        logMessage(INFO, "equipment added to player inventory : %s", equipment.name);
    }
}

void addConsumableToPlayerInventoryMenu(Player * player, Consumable consumable) {
    int selected = 0;
    int movement = 0;
    if (player->inventory->size < player->inventory->max_size) {
        do {
            system("/bin/stty cooked");
            cls();
            printf("\n\n Voulez-vous ajouter %s à votre inventaire ?\n", translate(consumable.name, player->translationList) );

            if (selected == 0) {
                printf("\x1b[30;47m(X) oui\x1b[0m\n");
                printf("() non\n");
            } else {
                printf("() oui\n");
                printf("\x1b[30;47m(X) non\x1b[0m\n");
            }
            printf("\nPress c to confirm\n");

            system("/bin/stty raw");
            movement = getchar();
            system("/bin/stty cooked");
            if (movement == 66 && selected < 1 || movement =='s') {
                selected++;
            } else if (movement == 65 && selected > 0) {
                selected--;
            }
        } while (movement != 'c' && movement != 'C');
    } else {
        do {
            system("/bin/stty cooked");
            cls();
            printf("\n\n L'inventaiter est plein, voulez-vous enlever un objet pour ajouter %s ?\n", translate(consumable.name, player->translationList) );

            if (selected == 0) {
                printf("\x1b[30;47m(X) oui\x1b[0m\n");
                printf("() non\n");
            } else {
                printf("() oui\n");
                printf("\x1b[30;47m(X) non\x1b[0m\n");
            }
            printf("\nPress c to confirm\n");

            system("/bin/stty raw");
            movement = getchar();
            system("/bin/stty cooked");
            if (movement == 66 && selected < 1 || movement =='s') {
                selected++;
            } else if (movement == 65 && selected > 0) {
                selected--;
            }
        } while (movement != 'c' && movement != 'C');

        if (selected == 0) {
            removeItemFromPlayerInventoryMenu(player);
        }
    }

    if (selected == 0) {
        addConsumableToPlayerInventory(player, consumable);
        logMessage(INFO, "equipment added to player inventory : %s", consumable.name);
    }
}