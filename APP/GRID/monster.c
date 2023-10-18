#include "monster.h"
#include <stdio.h>
#include <stdlib.h>

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

