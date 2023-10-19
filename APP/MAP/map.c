#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "time.h"

const int MAP_SIZE = 7;
const int MAX_BOSS_ROOM = 1;
const int MAX_STARTING_ROOM = 1;
const int MAC_SHOP_ROOM = 1;
const int MAX_ENNEMIES_ROOM = 20;

void printMap(char** map) {
    for (int i = 0; i < MAP_SIZE; i++) {
        for (int j = 0; j < MAP_SIZE; j++) {
            printf("%c ", map[i][j]);
        }
        printf("\n");
    }
}

void fillMap(char** map) {
    srand(time(NULL));
    int countBoss, countStarting, countShop, countEnnemies = 0;

    for (int i = 0; i < MAP_SIZE; i++) {
        for (int j = 0; j < MAP_SIZE; j++) {
            int check = 1;
            while(check != 0) {
                check = 0;
                int value = rand() % 6;
                switch (value) {
                    case 0 :
                        if (countBoss == MAX_BOSS_ROOM) {
                            map[i][j] = 'B'; 
                            countBoss++;
                        } else {
                            check++;
                        }
                        break;

                    case 1 :
                        if (countStarting < MAX_STARTING_ROOM) {
                            map[i][j] = 'X'; 
                            countStarting++;
                        } else {
                            check++;
                        }
                        break;
                        
                    case 2 :
                        if (countShop < MAC_SHOP_ROOM) {
                            map[i][j] = 'S'; 
                            countShop++;
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
                        map[i][j] = 'V';
                        break;

                    case 5 :
                        map[i][j] = 'R';
                        break;
                        
                }
            }
        }
    }
}

void freeMap(char** map) {
    for (int i = 0; i < MAP_SIZE; i++) {
        free(map[i]);
    }

    free(map);
}

void createMap() {
    char** map = malloc(sizeof(char*) * MAP_SIZE);

    for (int i = 0; i < MAP_SIZE; i++) {
        map[i] = malloc(sizeof(char) * MAP_SIZE);
    }

    fillMap(map);

    printMap(map);

    freeMap(map);
}

int main(int argc, char**argv) {
    
    createMap();

    return 0;
}