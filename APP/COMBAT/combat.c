#include "stdlib.h"
#include "math.h"
#include "time.h"
#include "combat.h"
#include "../PLAYER/player.h"
#include "../MAP/map.h"
#include "../UTILS/utils.h"
#include "../MONSTER/monster.h"

void startBattle(Player *player){
    cls();
    printf("Battle started !\n");
    srand(time(NULL));
    int nbMonsters = rand() % 3 + 1;
    Monster *monsters[nbMonsters];
    for (int i = 0; i < nbMonsters; i++) {
        monsters[i] = createMonster(player);
        printf("You are getting attacked by a %s !\n", monsters[i]->name);
    }
    // TODO: Create monsters in terminal
    //printf("This is your weapon : \n", player->weapon->name);

    return;
}