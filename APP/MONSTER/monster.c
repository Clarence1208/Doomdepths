#include "monster.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../PLAYER/player.h"

const int MONSTER_SIZE = 16;

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

void createSprite(Monster *monster, char *name) {
    char **sprite = malloc(sizeof(char*) * MONSTER_SIZE);
    for (int i = 0; i < MONSTER_SIZE; i++) {
        sprite[i] = malloc(sizeof(char) * MONSTER_SIZE);
    }

    if (strcmp(name, "Really Big Snail") == 0) {
        sprite[0] = "                                 ";
        sprite[1] = "                                 ";
        sprite[2] = "                                 ";
        sprite[3] = "                                 ";
        sprite[4] = "                                 ";
        sprite[5] = "                                 ";
        sprite[6] = "        o    o     __ __         ";
        sprite[7] = "         \\  /    '       `       ";
        sprite[8] = "          |/   /     __    \\     ";
        sprite[9] = "        (`  \\ '    '    \\   '    ";
        sprite[10] = "          \\  \\|   |   @_/   |    ";
        sprite[11] = "           \\   \\   \\       /--/  ";
        sprite[12] = "            ` ___ ___ ___ __ '   ";
        sprite[13] = "                                 ";
        sprite[14] = "                                 ";
        sprite[15] = "                                 ";
    } else if (strcmp(name, "Killer Bunny") == 0) {
        sprite[0] = "                  ";
        sprite[1] = "                  ";
        sprite[2] = "     _            ";
        sprite[3] = "    | \\      _    ";
        sprite[4] = "    |  \\   _/ |   ";
        sprite[5] = "    | |\\ //|  |   ";
        sprite[6] = "    |/ /o o\\| |   ";
        sprite[7] = "    _ |=(o)=| /   ";
        sprite[8] = "   | \\_/\\w/\\|/    ";
        sprite[9] = "    \\_      \\     ";
        sprite[10] = "      | /\\  )\\    ";
        sprite[11] = "      \\_\\/_/_)    ";
        sprite[12] = "       \"\"\"/  /    ";
        sprite[13] = "          \"\"\"   ";
        sprite[14] = "                  ";
        sprite[15] = "                  ";
    } else if (strcmp(name, "Gorilla") == 0) {

        sprite[0] = "                            ";
        sprite[1] = "                            ";
        sprite[2] = "                            ";
        sprite[3] = "           .\"`\".            ";
        sprite[4] = "       .-./ _=_ \\.-.        ";
        sprite[5] = "      {  (,(oYo),) }}       ";
        sprite[6] = "      {{ |   \"   |} }       ";
        sprite[7] = "      { { \\(---)/  }}       ";
        sprite[8] = "      {{  }'-=-'{ } }       ";
        sprite[9] = "      { { }._:_.{  }}       ";
        sprite[10] = "      {{  } -:- { } }       ";
        sprite[11] = "      {_{ }`===`{  _}       ";
        sprite[12] = "     ((((\\)     (/))))      ";
        sprite[13] = "                           ";
        sprite[14] = "                           ";
        sprite[15] = "                           ";

    } else if (strcmp(name, "Dragon") == 0) {
        sprite[0] = "                    ______________                  ";
        sprite[1] = "              ,===:'.,            `-._              ";
        sprite[2] = "                   `:.`---.__         `-._          ";
        sprite[3] = "                     `:.     `--.         `.        ";
        sprite[4] = "                      \\.        `.         `.       ";
        sprite[5] = "              (,,(,    \\.         `.   ____,-`.,    ";
        sprite[6] = "           (,'     `/   \\.   ,--.___`.'             ";
        sprite[7] = "       ,  ,'  ,--.  `,   \\.;'         `             ";
        sprite[8] = "       `{D, {    \\  :    \\;                         ";
        sprite[9] = "         V,,'    /  /    //                         ";
        sprite[10] = "         j;;    /  ,' ,-//.    ,---.      ,         ";
        sprite[11] = "         \\;'   /  ,' /  _  \\  /  _  \\   ,'/         ";
        sprite[12] = "               \\   `'  / \\  `'  / \\  `.' /          ";
        sprite[13] = "                `.___,'   `.__,'   `.__,           ";
        sprite[14] = "                                                   ";
        sprite[15] = "                                                   ";
    } else if (strcmp(name, "Goofy Ghost") == 0) {
        sprite[0] = "                     .---.                       ";
        sprite[1] = "                   /       \\                     ";
        sprite[2] = "     ---- _       |  O   O  |       _ ---        ";
        sprite[3] = "     \\       ~-.  `.       .'  .-~      /        ";
        sprite[4] = "       \\          ~-_>     <-~         /         ";
        sprite[5] = "        \\                             /          ";
        sprite[6] = "          \\                         /            ";
        sprite[7] = "            \\                     /              ";
        sprite[8] = "              \\                 /                ";
        sprite[9] = "                \\             /                  ";
        sprite[10] = "                  \\         /                    ";
        sprite[11] = "                    \\      /                     ";
        sprite[12] = "                      \\    \\                     ";
        sprite[13] = "                        \\   l                   ";
        sprite[14] = "                          \\ /                   ";
        sprite[15] = "                           V                    ";
    } else if (strcmp(name, "Mother Of Bats") == 0) {
        sprite[0] = "                                                                                     ";
        sprite[1] = "     ___------~~~~~~~~~~~----__         .:.         __----~~~~~~~~~~~------___      ";
        sprite[2] = "   ~~ ~--__          ......====\\\\~~    .:::.    ~~//====......          __--~ ~~     ";
        sprite[3] = "           ~\\ ...::::~~~~~~  //|||    .:::::.    |||\\\\  ~~~~~~::::... /~             ";
        sprite[4] = "          -~~\\_            //  |||***.(:::::).***|||  \\\\            _/~~-            ";
        sprite[5] = "               ~\\_        // *******.:|\\^^^/|:.******* \\\\        _/~                  ";
        sprite[6] = "                  \\      / ********.::(<: :>)::.******** \\      /               ";
        sprite[7] = "                   \\   /  ********.::::\\\\|//::::.********  \\   /                       ";
        sprite[8] = "                    \\ /   *******.:::::(o o):::::.*******   \\ /                       ";
        sprite[9] = "                     /.   ******.::::'*|V_V|***`::.******   .\\\\                       ";
        sprite[10] = "                       ~~--****.:::'***|___|*****`:.****--~~                          ";
        sprite[11] = "                             *.::'***//|___|\\\\*****`.*                               ";
        sprite[12] = "                             .:'  **/##|___|##\\\\**    .                              ";
        sprite[13] = "                            .    (v(VVV)___(VVV)v)                                  ";
        sprite[14] = "                                                                                  ";
        sprite[15] = "                                                                                  ";
    } else if (strcmp(name, "Golden Pig") == 0) {
        sprite[0] = "        d^b _,,ddP\"\"\"Ybb,,_ d^b";
        sprite[1] = "       d  ,dP\"'         \"Yb,  b";
        sprite[2] = "       b,d\"                 \"b,d";
        sprite[3] = "       d\"     ,d\"\"YgP\"\"b,     \"b";
        sprite[4] = "      d'      8  o g o  8      `b";
        sprite[5] = "      8       d,gPPPPRg,b       8";
        sprite[6] = "      8       dP'     'Yb       8";
        sprite[7] = "      8       8)  8 8  (8       8";
        sprite[8] = "      Y,      Yb       dP      ,P";
        sprite[9] = "       Ya      \"8ggggg8\"      aP";
        sprite[10] = "        \"Ya      b,,,d      aP\"";
        sprite[11] = "         8\"Yb,_         _,dP\"8";
        sprite[12] = "         8    8YbbgggddP8    8";
        sprite[13] = "         d    b         d    b";
        sprite[14] = "         \"\"\"\"\"\"         \"\"\"\"\"\"";
        sprite[15] = "                                    ";
    } else if (strcmp(name, "Mr Sananes") == 0) {
        sprite[1] = "             ";
        sprite[2] = "             ";
        sprite[3] = "             ";
        sprite[4] = "             ";
        sprite[5] = "             ";
        sprite[6] = "             ";
        sprite[7] = "             ";
        sprite[8] = "   c\"}       ";
        sprite[9] = "  ,(_).      ";
        sprite[10] = "   -\"-         ";
        sprite[11] = "             ";
        sprite[13] = "             ";
        sprite[14] = "             ";
        sprite[15] = "             ";
    } else if (strcmp(name, "King Dragon") == 0) {
        sprite[0] = "     (\\               /)      ";
        sprite[1] = "    __)\\             /(__     ";
        sprite[2] = "   __)_ \\  (\\!~!/)  / _(__    ";
        sprite[3] = "  __)_ `.\\  )d b(  /.' _(__   ";
        sprite[4] = " ___)_ `. \\(  _  )// .' _(___";
        sprite[5] = " )_  `. \\  ((q_p))  / .'  _(_";
        sprite[6] = " _)`.  \\  ,-)\\_/(-.  /  .'(_";
        sprite[7] = "  _) ,-._/v/vvvvv\\v\\_,-. (_";
        sprite[8] = "  _)///(._/v(___)v\\_.)\\\\\\(_";
        sprite[9] = "   \\_ ___/v(_____)v\\___ _/";
        sprite[10] = "     /vvv\\(_______)/vvv\\";
        sprite[11] = "     \\vvv/v(_____)v\\vvv/     ";
        sprite[12] = "     _\\vv\\\\v(___)v//vv/_";
        sprite[13] = "    '>_`  \\`-._.-'/  '_<;`";
        sprite[14] = "    ' >_,-'       `-._<`";
        sprite[15] = "                             ";
    } else if (strcmp(name, "Pig Who Stole Your Donut") == 0) {
        sprite[0] = "                             ";
        sprite[1] = "                             ";
        sprite[2] = "                             ";
        sprite[3] = "       __   __             ";
        sprite[4] = "       \\/---\\/           ";
        sprite[5] = "        ). .(           ";
        sprite[6] = "       ( (\") )           ";
        sprite[7] = "        )   (           ";
        sprite[8] = "       /     \\\\          ";
        sprite[9] = "      (       )        ";
        sprite[10] = "     ( \\ /-\\ / )          ";
        sprite[11] = "      w'W   W'w";
        sprite[12] = "                             ";
        sprite[13] = "                             ";
        sprite[14] = "                             ";
        sprite[15] = "                             ";
    } else {
        sprite[0] = "           ";
        sprite[1] = "           ";
        sprite[2] = "           ";
        sprite[3] = "           ";
        sprite[4] = "           ";
        sprite[5] = "  _______  ";
        sprite[6] = " /       \\ ";
        sprite[7] = "(  ERROR  )";
        sprite[8] = " \\_______/ ";
        sprite[9] = "  |     |  ";
        sprite[10] = "           ";
        sprite[11] = "           ";
        sprite[12] = "           ";
        sprite[13] = "           ";
        sprite[14] = "           ";
        sprite[15] = "           ";
    }
    monster->sprite = sprite;
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

    createSprite(monster, name);

    return monster;
}


Monster * createMonster(Player *player){
    int type = rand() % 5;
    switch (type) {
        case 0:
            return newMonster("Really Big Snail", 1 * player->map_level, 1 * player->map_level, 1 * player->map_level, player->map_level, 1);
            break;
        case 1:
            return newMonster("Killer Bunny", 1 * player->map_level, 1 * player->map_level, 1 * player->map_level, player->map_level, 1);
            break;
        case 2:
            return newMonster("Gorilla", 1 * player->map_level, 1 * player->map_level, 1 * player->map_level, player->map_level, 1);
            break;
        case 3:
            return newMonster("Dragon", 1 * player->map_level, 1 * player->map_level, 1 * player->map_level, player->map_level, 1);
            break;
        case 4:
            return newMonster("Goofy Ghost", 1 * player->map_level, 1 * player->map_level, 1 * player->map_level, player->map_level, 1);
            break;
    }
    return NULL;
}

Monster * createBoss(Player *player){
    int type = rand() % 5;
    switch (type) {
        case 0:
            return newMonster("Mother Of Bats", 1 * player->map_level, 1 * player->map_level, 1 * player->map_level, player->map_level, 1);
            break;
        case 1:
            return newMonster("Golden Pig", 1 * player->map_level, 1 * player->map_level, 1 * player->map_level, player->map_level, 1);
            break;
        case 2:
            return newMonster("Mr Sananes", 1 * player->map_level, 1 * player->map_level, 1 * player->map_level, player->map_level, 1);
            break;
        case 3:
            return newMonster("King Dragon", 1 * player->map_level, 1 * player->map_level, 1 * player->map_level, player->map_level, 1);
            break;
        case 4:
            return newMonster("Pig Who Stole Your Donut", 1 * player->map_level, 1 * player->map_level, 1 * player->map_level, player->map_level, 1);
            break;
    }
    return NULL;
}

void freeMonster(Monster *monster){
    free(monster->name);
    free(monster);
}
