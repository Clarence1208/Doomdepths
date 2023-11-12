#include "spell.h"

//
// Created by Clarence Hirsch on 18/10/2023.
//

#ifndef DOOMDEPTHS_SPELLS_H
#define DOOMDEPTHS_SPELLS_H

typedef struct Spells{
    Spell *spells;
    int size;
    int max_size;
} Spells;

Spells *create_spells(int max_size);

#endif //DOOMDEPTHS_SPELLS_H
