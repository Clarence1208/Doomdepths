//
// Created by Clarence Hirsch on 18/10/2023.
//

#ifndef DOOMDEPTHS_INVENTORY_H
#define DOOMDEPTHS_INVENTORY_H

#include "../EQUIPMENT/equipment.h"
#include "../CONSUMABLE/consumable.h"

typedef struct Inventory {
    Equipment *equipment;
    Consumable *consumable;
    int size;
    int max_size;
} Inventory;

#endif //DOOMDEPTHS_INVENTORY_H
