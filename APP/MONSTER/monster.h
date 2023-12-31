#ifndef DOOMDEPTHS_MONSTER_H
#define DOOMDEPTHS_MONSTER_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../PLAYER/player.h"

typedef struct Monster{
    char *name;
    int hp;
    int attack;
    int defense;
    int level;
    int experience; // how much experience the player gets for killing this monster
    int gold; // how much gold the player gets for killing this monster
    int type; // 1 = normal, 2 = boss
    char **sprite;
} Monster;

Monster *newMonster(char *name, int hp, int attack, int defense, int level, int type);

Monster *createMonster(Player *player);

Monster *createBoss(Player *player);

void printMonster(Monster *monster);

void printMonsterInfo(Monster *monster);

void freeMonster(Monster *monster);

#endif //DOOMDEPTHS_MONSTER_H