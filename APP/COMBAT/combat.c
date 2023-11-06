#include "stdlib.h"
#include "math.h"
#include "time.h"
#include "../PLAYER/player.h"
#include "../MAP/map.h"
#include "../UTILS/utils.h"

void startBattle(Player *player) {
    srand(time(NULL));
    nbEnnemies = rand() % 3 + 1;
    // TODO: Create ennemies
    printf("You are attacked by %d ennemies !\n", nbEnnemies);
    printf("This is your weapon : \n" player->weapon->name);

    return;
}