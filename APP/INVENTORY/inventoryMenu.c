//
// Created by Clarence Hirsch on 05/11/2023.
//

#include <stdio.h>
#include <stdlib.h>
#include "inventoryMenu.h"
#include "inventory.h"
#include "../UTILS/utils.h"
#include "../PLAYER/player.h"

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
        printf("Select an item : \n");
        printSelectionItemInventoryMenu(player->inventory, slotNbr, player->translationList);
        printf("movement : %d\n", movement);
        system("/bin/stty raw");
        //echap char to quit
        movement = getchar();
        system("/bin/stty cooked");
        if (movement == 66 && slotNbr < player->inventory->size - 1) {
            slotNbr++;
        } else if (movement == 65 && slotNbr > 0) {
            slotNbr--;
        }
        if (movement == 'e' || movement == 'E'){
            if (isSlotEquipment(player->inventory, slotNbr)) {
                if (isSlotWeapon(player->inventory, slotNbr)){
                    equipWeaponFromInventory(player, slotNbr);
                }else {
                    equipArmorFromInventory(player, slotNbr);
                }
            } else {
               // useItem(player, slotNbr);
            }
            break;
        }
    } while (movement != 'p' && movement != 'P');


}