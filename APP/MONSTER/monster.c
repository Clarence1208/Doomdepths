//
// Created by Clarence Hirsch on 19/10/2023.
//

#include "monster.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Monster * newMonster(char * name, int hp, int attack, int defense, int speed, int level, int type){
    Monster * monster = malloc(sizeof(Monster*));
    monster->name = malloc(sizeof(char) * strlen(name));
    strcpy(monster->name, name);
    monster->hp = hp;
    monster->attack = attack;
    monster->defense = defense;
    monster->speed = speed;
    monster->level = level;
    monster->type = type;

    return monster;
}

void printMonsterInfo(Monster * monster){
    printf("Name : %s\n", monster->name);
    printf("HP : %d\n", monster->hp);
    printf("Attack : %d\n", monster->attack);
    printf("Defense : %d\n", monster->defense);
    printf("Speed : %d\n", monster->speed);
    printf("Level : %d\n", monster->level);
    printf("Type : %s\n", monster->type);
}

void printMonster(Monster * monster){

}