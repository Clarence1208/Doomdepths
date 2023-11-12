//
// Created by Clarence Hirsch on 12/11/2023.
//

#ifndef DOOMDEPTHS_SHOP_H
#define DOOMDEPTHS_SHOP_H

#include "../PLAYER/player.h"

Equipment **createEquipmentsForSale(Player *player);

Consumable **createConsumablesForSale(Player *player);

void enterShop(Player * player);

#endif //DOOMDEPTHS_SHOP_H
