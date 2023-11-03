//
// Created by Clarence Hirsch on 19/10/2023.
//

#ifndef DOOMDEPTHS_MONSTER_H
#define DOOMDEPTHS_MONSTER_H

typedef struct Monster{
    char * name;
    int hp;
    int attack;
    int defense;
    int speed;
    int level;
    int type;
} Monster;

Monster * newMonster(char * name, int hp, int attack, int defense, int speed, int level, int type);

void printMonster(Monster * monster);

void printMonsterInfo(Monster * monster);

#endif //DOOMDEPTHS_MONSTER_H
