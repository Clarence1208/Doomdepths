// Creation date: 08-11-2023
// Author: Nino PLANE
// Last modified: 08-11-2023

#include "../UTILS/utils.h"
#include "stdio.h"
#include "stdlib.h"
#include "spell.h"
#include "string.h"

Spell * newSpell(char * name, char * description, int spellEffectivenessValue, int manaCost, int levelToUnlock, enum SpellType spellType) {
    Spell *spell = malloc(sizeof(Spell*));
    spell->name = malloc(sizeof(char) * strlen(name) + 1);
    strcpy(spell->name, name);
    spell->description = malloc(sizeof(char) * strlen(description) + 1);
    strcpy(spell->description, description);
    spell->spellEffectivenessValue = spellEffectivenessValue;
    spell->manaCost = manaCost;
    spell->levelToUnlock = levelToUnlock;
    spell->type = spellType;
    return spell;
}

Spell ** loadSpells(){
    Spell **spells = malloc(sizeof(Spell**) * 9);

    spells[0] = newSpell("Fireball", "A fireball that deals quite good damage to one monster", 25, 20, 0, Fireball);
    spells[1] = newSpell("Big Fireball", "A fireball that deals big damage to one monster", 60, 30, 6, Fireball);
    spells[2] = newSpell("Bang", "A bang that deals quite good damage to all monsters", 25, 20, 3, Bang);
    spells[3] = newSpell("Big Bang", "A bang that deals big damage to all monsters", 60, 30, 8, Bang);
    spells[4] = newSpell("Heal", "A heal that heals quite good health", 75, 20, 0, Heal);
    spells[5] = newSpell("Big Heal", "A heal that heals big health", 200, 30, 7, Heal);
    spells[6] = newSpell("Focus", "A spell that regenerates a little bit of mana", 40, 0, 2, Mana);
    spells[7] = newSpell("Money Rain", "A spell that makes monsters drop more gold", 0, 30, 4, Money);
    spells[8] = newSpell("Experience Rain", "A spell that makes monsters drop more experience", 0, 50, 5, Experience);

    return spells;
}


void freeSpell(Spell *spell) {
    free(spell->name);
    free(spell->description);
    free(spell);
}

void freeSpells(Spell **spells) {
    for (int i = 0; i < 9; i++) {
        freeSpell(spells[i]);
    }
    free(spells);
}