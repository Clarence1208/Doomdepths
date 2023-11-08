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

Monster *newMonster(char *name, int hp, int attack, int defense, int level, int type) {
    Monster *monster = malloc(sizeof(Monster));
    if (monster == NULL) {
        fprintf(stderr, "Failed to allocate memory for Monster structure\n");
        return NULL;
    }

    monster->name = malloc(sizeof(char) * (strlen(name) + 1));
    if (monster->name == NULL) {
        fprintf(stderr, "Failed to allocate memory for monster name\n");
        free(monster);
        return NULL;
    }

    // Initialize the monster attributes
    monster->hp = hp;
    monster->attack = attack;
    monster->defense = defense;
    monster->level = level;
    monster->experience = hp * level;
    monster->gold = attack * level;
    monster->type = type;
    
    // Copy the name to monster->name
    strcpy(monster->name, name);

    return monster;
}


Monster * createMonster(Player *player){
    int type = rand() % 5;
    switch (type) {
        case 0:
            return newMonster("Goblin", 1 * player->map_level, 1 * player->map_level, 1 * player->map_level, player->map_level, 1);
            break;
        case 1:
            return newMonster("Orc", 1 * player->map_level, 1 * player->map_level, 1 * player->map_level, player->map_level, 1);
            break;
        case 2:
            return newMonster("Troll", 1 * player->map_level, 1 * player->map_level, 1 * player->map_level, player->map_level, 1);
            break;
        case 3:
            return newMonster("Dragon", 1 * player->map_level, 1 * player->map_level, 1 * player->map_level, player->map_level, 1);
            break;
        case 4:
            return newMonster("Demon", 1 * player->map_level, 1 * player->map_level, 1 * player->map_level, player->map_level, 1);
            break;
    }
    return NULL;
}

Monster * createBoss(Player *player){
    int type = rand() % 5;
    switch (type) {
        case 0:
            return newMonster("King Goblin", 1 * player->map_level, 1 * player->map_level, 1 * player->map_level, player->map_level, 1);
            break;
        case 1:
            return newMonster("King Orc", 1 * player->map_level, 1 * player->map_level, 1 * player->map_level, player->map_level, 1);
            break;
        case 2:
            return newMonster("King Troll", 1 * player->map_level, 1 * player->map_level, 1 * player->map_level, player->map_level, 1);
            break;
        case 3:
            return newMonster("King Dragon", 1 * player->map_level, 1 * player->map_level, 1 * player->map_level, player->map_level, 1);
            break;
        case 4:
            return newMonster("King Demon", 1 * player->map_level, 1 * player->map_level, 1 * player->map_level, player->map_level, 1);
            break;
    }
}

void freeMonster(Monster *monster){
    free(monster->name);
    free(monster);
}

