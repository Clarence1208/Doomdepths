//
// Created by Clarence Hirsch on 18/10/2023.
//

#include "inventory.h"
#include <stdlib.h>

Inventory *create_inventory(int max_size) {
    Inventory *inventory = malloc(sizeof(Inventory));
    Equipment *equipment = malloc(sizeof(Equipment) * max_size);
    Consumable *consumable = malloc(sizeof(Consumable) * max_size);
    inventory->equipment = equipment;
    inventory->consumable = consumable;
    inventory->size = 0;
    inventory->max_size = max_size;
    return inventory;
}
