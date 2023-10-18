#ifndef MONSTER_H
#define MONSTER_H

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

#endif MONSTER_H