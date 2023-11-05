#ifndef DOOMDEPTHS_MAP_H
#define DOOMDEPTHS_MAP_H

#include "../PLAYER/player.h"
#include "../UTILS/utils.h"
#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "time.h"

void cls();

void movePlayer(Player *player, char **map, char direction);

void printMap(char **map);

void fillMap(char **map, Player *player);

void freeMap(char **map);

void printPlayableMap(char **map, Player *player);

void createMap(Player *player);

#endif //DOOMDEPTHS_MAP_H