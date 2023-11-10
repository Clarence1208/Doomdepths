// Creation date: 16-10-2023
// Author: Nino PLANE
// Last modified: 06-11-2023

#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "time.h"
#include "map.h"
#include "../PLAYER/player.h"
#include "../UTILS/utils.h"
#include "../COMBAT/combat.h"

const int MAP_SIZE = 7;
const int MAP_TILE_SIZE = 5;
const int MAX_BOSS_ROOM = 1;
const int MAX_STARTING_ROOM = 1;
const int MAX_SHOP_ROOM = 1;
const int MAX_ENNEMIES_ROOM = 20;
const int MAX_VOID_ROOM = 15;


void movePlayer(Player* player, char** map, char movement) {
    map[player->x][player->y] = 'R';
    char tile = '0';
    switch (movement) {
        case 'z' :
            if (player->x > 0) {
                if (map[player->x-1][player->y] != 'V') {
                    player->x--;
                    tile = map[player->x][player->y];
                }
            }
            break;
        case 'q' :
            if (player->y > 0) {
                if (map[player->x][player->y-1] != 'V') {
                    player->y--;
                    tile = map[player->x][player->y];
                }
            }
            break;
        case 's' :
            if (player->x < MAP_SIZE-1) {
                if (map[player->x+1][player->y] != 'V') {
                    player->x++;
                    tile = map[player->x][player->y];
                }
            }
            break;
        case 'd' :
            if (player->y < MAP_SIZE-1) {
                if (map[player->x][player->y+1] != 'V') {
                    player->y++;
                    tile = map[player->x][player->y];
                }
            }
            break;
    }

    if (tile == 'E') {
        startBattle(player, 0);
    } else if (tile == 'S') {
        // TO DO : Create shop
        //startShop(player);
    } else if (tile == 'B') {
        startBattle(player, 1);
        freeMap(map);
        createMap(player);
    }
}

void printMap(char** map) {
    for (int i = 0; i < MAP_SIZE; i++) {
        for (int j = 0; j < MAP_SIZE; j++) {
            printf("%c ", map[i][j]);
        }
        printf("\n");
    }
}

void fillMap(char** map, Player* player) {
    srand(time(NULL));
    int countStarting = 0;
    int countBoss = 0;
    int countShop = 0;
    int countVoid = 0;
    int countEnnemies = 0;
    int sizeBoss = 0;
    int sizeStarting = 0;
    int sizeShop = 0;
    int sizeVoid = 0;

    for (int i = 0; i < MAP_SIZE; i++) {
        for (int j = 0; j < MAP_SIZE; j++) {
            int check = 1;
            while(check != 0) {
                check = 0;
                int value = rand() % 6;
                switch (value) {
                    case 0 :
                        if (sizeBoss == (MAP_SIZE/2)+1) {
                            map[i][j] = 'B'; 
                            countBoss++;
                            sizeBoss++;
                        } else if (countBoss < MAX_BOSS_ROOM) {
                            sizeBoss++;
                            check++;
                        } else {
                            check++;
                        }
                        break;

                    case 1 :
                        if (sizeStarting == (MAP_SIZE/2)+2) {
                            map[i][j] = 'X'; 
                            countStarting++;
                            sizeStarting++;
                            player->x = i;
                            player->y = j;
                        } else if (countStarting < MAX_STARTING_ROOM) {
                            sizeStarting++;
                            check++;
                        } else {
                            check++;
                        }
                        break;
                        
                    case 2 :
                        if (sizeShop == (MAP_SIZE/2)+3) {
                            map[i][j] = 'S'; 
                            countShop++;
                            sizeShop++;
                        } else if (countShop < MAX_SHOP_ROOM) {
                            sizeShop++;
                            check++;
                        } else {
                            check++;
                        }
                        break;
                        
                    case 3 :
                        if (countEnnemies < MAX_ENNEMIES_ROOM) {
                            map[i][j] = 'E'; 
                            countEnnemies++;
                        } else {
                            check++;
                        }
                        break;
                        
                    case 4 :
                        if (countVoid < MAX_VOID_ROOM) {
                            if (i > 0 && j > 0 && i < MAP_SIZE-1 && j < MAP_SIZE-1) {
                                if (map[i-1][j] != 'V' && map[i+1][j] != 'V' && map[i][j-1] != 'V' && map[i][j+1] != 'V' && map[i+1][j+1] != 'V' && map[i-1][j+1] != 'V' && map[i+1][j-1] != 'V' && map[i-1][j-1] != 'V') {
                                    map[i][j] = 'V'; 
                                    countVoid++;
                                } else {
                                    check++;
                                }
                            } else {
                                check++;
                            }
                        } else {
                            check++;
                        }
                        break;  
                        
                    case 5 :
                        map[i][j] = 'R';
                        break;
                        
                }
            }
        }
    }

    if (countBoss != 1 || countShop != 1 || countStarting != 1) {
        printf("Ok\n");
        fillMap(map, player);
    }

}

void freeMap(char** map) {
    for (int i = 0; i < MAP_SIZE; i++) {
        free(map[i]);
    }

    free(map);
}

void printPlayableMap(char** map, Player* player) {
    cls();
    printf("Dungeon Level : %d\n\n", player->map_level);
    int count = 0;
    for (int i = 0; i < MAP_SIZE; count++) {
        if (count == MAP_TILE_SIZE-1 && count != 0) {
            i++;
            count = 0;
        }
        if (i == MAP_SIZE) {
            break;
        }
        for (int j = 0; j < MAP_SIZE; j++) {
            for (int k = 0; k < MAP_TILE_SIZE; k++) {
                if (i == player->x && j == player->y) {
                    for(int l = 0; l < MAP_TILE_SIZE; l++) {
                        printf("\033[1;34m%c\033[0m", 'X');
                    }
                    break;
                }
                if (map[i][j] == 'B') {
                    printf("\033[1;35m%c\033[0m", 'X');
                } else if (map[i][j] == 'S') {
                    printf("\033[1;32m%c\033[0m", 'X');
                } else if (map[i][j] == 'X') {
                    printf("X");
                } else if (map[i][j] == 'R') {
                    printf("X");
                } else if (map[i][j] == 'V') {
                    printf(" ");
                } else if (map[i][j] == 'E') {
                    printf("\033[1;31m%c\033[0m", 'X');
                }
            }
        }
        printf("\n");
    }
}

void createMap(Player* player) {
    char** map = malloc(sizeof(char*) * MAP_SIZE);

    for (int i = 0; i < MAP_SIZE; i++) {
        map[i] = malloc(sizeof(char) * MAP_SIZE);
    }

    fillMap(map, player);

    cls();

    printPlayableMap(map, player);
    
    char movement = 0;
    while (movement != 'p' && movement != 'P'){
        
        printf("Move around with ZQSD, see your player infos with 'a' or 'p' to exit game !\n\n");
        system("/bin/stty raw");
        movement = getchar();
        system("/bin/stty cooked");
        movePlayer(player, map, movement);
        cls();
        if (movement == 'a') {
            printPlayer(player);
        }
        printPlayableMap(map, player);

    };

    system("/bin/stty cooked");

    // TO DO : Save the game

    //freeMap(map); TO DO NEED TO BE FIXED
    //freePlayer(player); TO DO NEED TO BE FIXED
}

void startTest() {

    Player* player = malloc(sizeof(Player));
    player->health = 100;
    player->max_health = 100;
    player->mana = 100;
    player->max_mana = 100;
    player->attack = 10;
    player->level = 30;
    player->map_level = 1;
    player->experience = 0;
    player->gold = 0;
    player->x = 0;
    player->y = 0;
    player->weapon = createDefaultWeapon();
    player->armor = createDefaultArmor();
    
    createMap(player);

    return;
}