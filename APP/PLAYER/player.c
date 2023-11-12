#include "player.h"
#include <stdlib.h>
#include <stdio.h>
#include "string.h"
#include "../UTILS/utils.h"

Player * newPlayer(char * name){
    Player *player = malloc(sizeof(Player));
    player->name = malloc(sizeof(char) * strlen(name) + 1);
    strcpy(player->name, name);
    player->health = 100;
    player->max_health = 100;
    player->mana = 100;
    player->max_mana = 100;
    player->attack = 10;
    player->level = 1;
    player->map_level = 1;
    player->experience = 0;
    player->gold = 0;
    player->x = 0;
    player->y = 0;

    player->weapon = createDefaultWeapon();
    player->armor = createDefaultArmor();


    return player;
}

void freePlayer(Player *player){
    free(player->name);
    // weapon and armor need to be fixed
    if (player->weapon != NULL) {
        free(player->weapon->name);
        free(player->weapon->description);
        free(player->weapon);
    }
    if (player->armor != NULL) {
        free(player->armor->name);
        free(player->armor->description);
        free(player->armor);
    }
    free(player);
}

void printPlayer(Player *player){
    cls();
    printf("Player infos :\n");
    if (player->name != NULL) {
        printf("Name : %s\n", player->name);
    } else {
        printf("Name : Unknown\n");
    }
    printf("HP : %d / %d\n", player->health, player->max_health);
    printf("Mana : %d / %d\n", player->mana, player->max_mana);
    printf("Attack : %d\n", player->attack);
    printf("Level : %d\n", player->level);
    printf("Experience : %d\n", player->experience);
    printf("Gold : %d\n", player->gold);
    if (player->weapon != NULL) {
        printf("Weapon : %s\n", player->weapon->name);
    } else {
        printf("Weapon : Bare Hands\n");
    }
    if (player->armor != NULL) {
        printf("Armor : %s\n", player->armor->name);
    } else {
        printf("Armor : Dirty Shirt\n");
    }

    printf("\nPress any key to continue...\n");
    system("/bin/stty raw");
    char wait = getchar();
    system("/bin/stty cooked");
    return;
}