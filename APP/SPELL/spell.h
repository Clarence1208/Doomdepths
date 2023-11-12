// Creation date: 08-11-2023
// Author: Nino PLANE
// Last modified: 08-11-2023

#ifndef DOOMDEPTHS_SPELL_H
#define DOOMDEPTHS_SPELL_H

#include "../UTILS/utils.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

enum SpellType {
    Fireball,
    Bang,
    Heal,
    Mana,
    Money,
    Experience
};

typedef struct Spell {
    char *name;
    char *description;
    int spellEffectivenessValue;
    int manaCost;
    int levelToUnlock;
    enum SpellType type;
} Spell;

Spell *newSpell(char *name, char *description, int spellEffectivenessValue, int manaCost, int levelToUnlock, enum SpellType type);

Spell **loadSpells();

void freeSpell(Spell *spell);

void freeSpells(Spell **spells);

#endif //DOOMDEPTHS_SPELL_H
