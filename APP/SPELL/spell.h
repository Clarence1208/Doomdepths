//
// Created by Clarence Hirsch on 18/10/2023.
//

#ifndef DOOMDEPTHS_SPELL_H
#define DOOMDEPTHS_SPELL_H

enum SpellType {
    Offensive,
    Defensive,
    Healing
};

typedef struct Spell {
    char *name;
    char *description;
    int spellEffectivenessValue;
    enum SpellType type;
} Spell;

#endif //DOOMDEPTHS_SPELL_H
