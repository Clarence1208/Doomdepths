#include "monster.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../PLAYER/player.h"

void printMonsterInfo(Monster * monster){
    printf("Name : %s\n", monster->name);
    printf("HP : %d\n", monster->hp);
    printf("Attack : %d\n", monster->attack);
    printf("Defense : %d\n", monster->defense);
    printf("Level : %d\n", monster->level);
    printf("Experience : %d\n", monster->experience);
    printf("Type : %d\n", monster->type);
}

void printMonster(Monster * monster){

}

Monster * newMonster(char *name, int hp, int attack, int defense, int level, int type){
    Monster *monster = malloc(sizeof(Monster*));
    monster->name = malloc(sizeof(char) * strlen(name));
    strcpy(monster->name, name);
    monster->hp = hp;
    monster->attack = attack;
    monster->defense = defense;
    monster->level = level;
    monster->experience = hp * level;
    monster->type = type;
    return monster;
}

Monster * createMonster(Player * player){
    int type = rand() % 5;
    switch (type) {
        case 0:
            return newMonster("Goblin", 10 * player->map_level, 5 * player->map_level, 2 * player->map_level, player->map_level, 1);
            break;
        case 1:
            return newMonster("Orc", 15 * player->map_level, 7 * player->map_level, 3 * player->map_level, player->map_level, 2);
            break;
        case 2:
            return newMonster("Troll", 20 * player->map_level, 10 * player->map_level, 5 * player->map_level, player->map_level, 3);
            break;
        case 3:
            return newMonster("Dragon", 50 * player->map_level, 20 * player->map_level, 10 * player->map_level, player->map_level, 4);
            break;
        case 4:
            return newMonster("Demon", 100 * player->map_level, 50 * player->map_level, 20 * player->map_level, player->map_level, 5);
            break;
    }
    return NULL;
}

