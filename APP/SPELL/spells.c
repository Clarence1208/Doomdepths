//
// Created by Clarence Hirsch on 18/10/2023.
//

#include "spells.h"
#include <stdlib.h>

Spells *create_spells(int max_size) {
    Spells *spells = malloc(sizeof(Spells));
    spells->spells = malloc(sizeof(Spell) * max_size);
    spells->size = 0;
    spells->max_size = max_size;
    return spells;
}