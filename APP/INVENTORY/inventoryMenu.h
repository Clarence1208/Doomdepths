//
// Created by Clarence Hirsch on 05/11/2023.
//

#ifndef DOOMDEPTHS_INVENTORYMENU_H
#define DOOMDEPTHS_INVENTORYMENU_H

#include "../MESSAGE_RESOLVER/messageResolver.h"
#include "inventory.h"
#include "../PLAYER/player.h"

void printSelectionItemInventoryMenu (Inventory * inventory, int selectedItem, TranslationList * translationList);

void selectableItemInventoryMenu (Player * player);

int addEquipmentToPlayerInventoryMenu(Player * player, Equipment equipment);

int addConsumableToPlayerInventoryMenu(Player * player, Consumable consumable);

#endif //DOOMDEPTHS_INVENTORYMENU_H
