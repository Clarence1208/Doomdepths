#include "player.h"
#include <stdlib.h>
#include <stdio.h>
#include "string.h"

Player * newPlayer(char * name){
    Player *player = malloc(sizeof(Player*));
    player->name = malloc(sizeof(char) * strlen(name));
    strcpy(player->name, name);
    player->health = 100;
    player->max_health = 100;
    player->mana = 100;
    player->max_mana = 100;
    player->attack = 10;
    player->level = 0;
    player->experience = 0;
    player->gold = 0;
    player->x = 0;
    player->y = 0;

    player->weapon = malloc(sizeof(Equipment*));
    player->armor = malloc(sizeof(Equipment*));


    return player;
}