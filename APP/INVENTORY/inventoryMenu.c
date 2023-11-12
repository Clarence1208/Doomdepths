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
        // "%s is equipped as weapon\n"
        printf("%s %s\n",
               translate(player->weapon->name, player->translationList),
               translate("equipedAsWeapon", player->translationList));
        // "%s is equipped as armor\n"
        printf("%s %s\n",
               translate(player->armor->name, player->translationList),
               translate("equipedAsArmor", player->translationList));
        // "Select an item : \n"
        printf("\n%s\n", translate("selectItem", player->translationList));
        printSelectionItemInventoryMenu(player->inventory, slotNbr, player->translationList);
        // "Press c to use selected item\n"
        printf("\n%s\n", translate("useItemAction", player->translationList));
        // "Press p to exit inventory\n"
        printf("%s\n", translate("exitInventory", player->translationList));
//        printf("movement : %d\n", movement);
        system("/bin/stty raw");
        movement = getchar();
        system("/bin/stty cooked");
        if (movement == 66 && slotNbr < player->inventory->size - 1) {
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
        // "%s is equipped as weapon\n"
        printf("%s %s\n",
               translate(player->weapon->name, player->translationList),
               translate("equipedAsWeapon", player->translationList));
        // "%s is equipped as armor\n"
        printf("%s %s\n",
               translate(player->armor->name, player->translationList),
               translate("equipedAsArmor", player->translationList));
        // "Select an item to remove from player inventory : \n"
        printf("\n%s\n", translate("selectItemToRemove", player->translationList));
        printSelectionItemInventoryMenu(player->inventory, slotNbr, player->translationList);
        printf("\n%s\n", translate("useItemAction", player->translationList));
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


int addEquipmentToPlayerInventoryMenu(Player * player, Equipment equipment) {
    int selected = 0;
    int movement = 0;
    if (player->inventory->size < player->inventory->max_size) {
        do {
            system("/bin/stty cooked");
            cls();
            // "Do you want to buy %s and add it to your inventory ?\n"
            printf("\n\n%s %s %s\n",
                translate("addItem", player->translationList),
                translate(equipment.name, player->translationList),
                translate("addItem2", player->translationList));

            if (selected == 0) {
                printf("\x1b[30;47m(X) %s\x1b[0m\n", translate("yes", player->translationList));
                printf("() %s\n", translate("no", player->translationList));
            } else {
                printf("() %s\n", translate("yes", player->translationList));
                printf("\x1b[30;47m(X) %s\x1b[0m\n", translate("no", player->translationList));
            }
            // "Press c to confirm\n"
            printf("\n%s\n", translate("confirmAction", player->translationList));

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
            // "Your inventory is full, do you want to remove an item to add %s ?\n"
            printf("\n\n%s %s ?\n",
                     translate("inventoryFull", player->translationList),
                   translate(equipment.name, player->translationList));

            if (selected == 0) {
                printf("\x1b[30;47m(X) %s\x1b[0m\n", translate("yes", player->translationList));
                printf("() %s\n", translate("no", player->translationList));
            } else {
                printf("() %s\n", translate("yes", player->translationList));
                printf("\x1b[30;47m(X) %s\x1b[0m\n", translate("no", player->translationList));
            }
            printf("\n%s\n", translate("confirmAction", player->translationList));

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
        player->gold -= equipment.price;
        logMessage(INFO, "equipment added to player inventory : %s", equipment.name);
        return 1;
    }
    return 0;
}

int addConsumableToPlayerInventoryMenu(Player * player, Consumable consumable) {
    int selected = 0;
    int movement = 0;
    if (player->inventory->size < player->inventory->max_size) {
        do {
            system("/bin/stty cooked");
            cls();
            // "Do you want to add %s to your inventory ?\n"
            printf("\n\n%s %s %s\n",
                    translate("addItem", player->translationList),
                    translate(consumable.name, player->translationList),
                    translate("addItem2", player->translationList));

            if (selected == 0) {
                printf("\x1b[30;47m(X) %s\x1b[0m\n", translate("yes", player->translationList));
                printf("() %s\n", translate("no", player->translationList));
            } else {
                printf("() %s\n", translate("yes", player->translationList));
                printf("\x1b[30;47m(X) %s\x1b[0m\n", translate("no", player->translationList));
            }
            printf("\n%s\n", translate("confirmAction", player->translationList));

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
            printf("\n\n%s %s ?\n",
                     translate("inventoryFull", player->translationList),
                   translate(consumable.name, player->translationList) );

            if (selected == 0) {
                printf("\x1b[30;47m(X) %s\x1b[0m\n", translate("yes", player->translationList));
                printf("() %s\n", translate("no", player->translationList));
            } else {
                printf("() %s\n", translate("yes", player->translationList));
                printf("\x1b[30;47m(X) %s\x1b[0m\n", translate("no", player->translationList));
            }
            printf("\n%s\n", translate("confirmAction", player->translationList));

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
        player->gold -= consumable.price;
        logMessage(INFO, "equipment added to player inventory : %s", consumable.name);
        return 1;
    }
    return 0;
}