#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "time.h"

const int MAP_SIZE = 7;
const int MAP_TILE_SIZE = 5;
const int MAX_BOSS_ROOM = 1;
const int MAX_STARTING_ROOM = 1;
const int MAX_SHOP_ROOM = 1;
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
    int countStarting = 0;
    int countBoss = 0;
    int countShop = 0;
    int countEnnemies = 0;
    int sizeBoss = 0;
    int sizeStarting = 0;
    int sizeShop = 0;

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
                        map[i][j] = 'V';
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
        fillMap(map);
    }
}

void freeMap(char** map) {
    for (int i = 0; i < MAP_SIZE; i++) {
        free(map[i]);
    }

    free(map);
}

void printPlayableMap(char** map) {
    int count = 0;
    for (int i = 0; i < MAP_SIZE; count++) {
        if (count % MAP_TILE_SIZE == 0 && count != 0) {
            i++;
        }
        if (i == MAP_SIZE) {
            break;
        }
        for (int j = 0; j < MAP_SIZE; j++) {
            for (int k = 0; k < MAP_SIZE; k++) {
                if (map[i][j] == 'B') {
                    printf("\033[1;35m%c\033[0m", 'X');
                } else if (map[i][j] == 'S') {
                    printf("\033[1;32m%c\033[0m", 'X');
                } else if (map[i][j] == 'R' || map[i][j] == 'X') {
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

void createMap() {
    char** map = malloc(sizeof(char*) * MAP_SIZE);

    for (int i = 0; i < MAP_SIZE; i++) {
        map[i] = malloc(sizeof(char) * MAP_SIZE);
    }

    fillMap(map);

    //printMap(map);

    printPlayableMap(map);

    freeMap(map);
}

int main(int argc, char**argv) {
    
    createMap();

    return 0;
}