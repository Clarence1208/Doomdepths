#include "stdlib.h"
#include "math.h"
#include "time.h"
#include "combat.h"
#include "../PLAYER/player.h"
#include "../MAP/map.h"
#include "../UTILS/utils.h"
#include "../MONSTER/monster.h"

void popMonster(Monster **monsters, int index, int nbMonsters) {
    for (int i = index; i < nbMonsters-1; i++) {
        monsters[i] = monsters[i+1];
    }
}

void startBattle(Player *player){
    cls();
    printf("Battle started !\n\n");
    srand(time(NULL));
    int nbMonsters = rand() % 3 + 1;
    Monster *monsters[nbMonsters];
    for (int i = 0; i < nbMonsters; i++) {
        monsters[i] = createMonster(player);
        printf("You are getting attacked by a %s !\n", monsters[i]->name);
    }

    printf("\n");

    // TODO: Create monsters in terminal

    int turn = 0;
    int playerTurn = 1;
    int monsterTurn = 0;
    // int monsterTurns[nbMonsters];
    // for (int i = 0; i < nbMonsters; i++) {
    //     monsterTurns[i] = 1;
    // }
    while (1) {
        if (playerTurn) {
            printf("It's your turn !\n");
            if (player->weapon != NULL) {
                printf("You can attack %d times\n", player->weapon->nbAttack);
            } else {
                printf("You can attack once\n");
            }
            char input = '0';
            while (input != 'a' && input != 'p') {
                printf("Press 'a' to attack or 'p' to pass your turn\n");
                system("/bin/stty raw");
                input = getchar();
                system("/bin/stty cooked");
            }
            if (input == 'a') {
                int amountAttack = 1;
                if (player->weapon != NULL) {
                    amountAttack = player->weapon->nbAttack;
                }
                while(amountAttack > 0) {
                    int choice = 0;
                    while(choice < 1 || choice > nbMonsters) {
                        //int count = 1;
                        cls();
                        printf("You have %d attacks left\n", amountAttack);
                        printf("Choose a monster to attack : \n");
                        for(int k = 0; k < nbMonsters; k++) {
                            //if (monsterTurns[k]) {
                                printf("%d : %s\n", k+1, monsters[k]->name);
                                //count++;
                            //}
                        }
                        system("/bin/stty raw");
                        input = getchar();
                        system("/bin/stty cooked");
                        choice = input - '0';
                    }
                    cls();
                    int damage = 0;
                    if (player->weapon != NULL) {
                        damage = player->attack + player->weapon->equipmentEffectivenessValue - monsters[choice-1]->defense;
                    } else {
                        damage = player->attack - monsters[choice-1]->defense;
                    }
                    if (damage < 0) {
                        damage = 0;
                    }
                    monsters[choice-1]->hp -= damage;
                    printf("You attacked the %s for %d damage\n", monsters[choice-1]->name, damage);
                    if (monsters[choice-1]->hp <= 0) {
                        printf("\nYou killed the %s !\n", monsters[choice-1]->name);
                        player->experience += monsters[choice-1]->experience;
                        player->gold += monsters[choice-1]->gold;
                        printf("You gained %d experience !\n", monsters[choice-1]->experience);
                        printf("You gained %d gold !\n", monsters[choice-1]->gold);
                        popMonster(monsters, choice-1, nbMonsters);
                        nbMonsters--;
                    }
                    printf("\nPress any key to continue...\n");
                    system("/bin/stty raw");
                    char wait = getchar();
                    system("/bin/stty cooked");
                    cls();
                    amountAttack--;
                }
            } else {
                    // for (int j = 0; j < nbMonsters; j++) {
                    //     if (monsterTurns[j]) {
                    //         int damage = player->attack - monsters[j]->defense;
                    //         if (damage < 0) {
                    //             damage = 0;
                    //         }
                    //         monsters[j]->hp -= damage;
                    //         printf("You attacked the %s for %d damage\n", monsters[j]->name, damage);
                    //         if (monsters[j]->hp <= 0) {
                    //             printf("You killed the %s !\n", monsters[j]->name);
                    //             player->experience += monsters[j]->experience;
                    //             printf("You gained %d experience !\n", monsters[j]->experience);
                    //             monsterTurns[j] = 0;
                    //         }
                    //     }
                    // }
                }
            // playerTurn = 0;
            // monsterTurn = 1;
            } else if (monsterTurn) {
                // printf("It's the monsters' turn !\n");
                // for (int i = 0; i < nbMonsters; i++) {
                // if (monsterTurns[i]) {
                //     int damage = monsters[i]->attack - player->armor->equipmentEffectivenessValue;
                //     if (damage < 0) {
                //         damage = 0;
                //     }
                //     player->health -= damage;
                //     printf("The %s attacked you for %d damage\n", monsters[i]->name, damage);
                //     if (player->health <= 0) {
                //         printf("You died !\n");
                //         exit(0);
                //     }
                // }
            }
            // monsterTurn = 0;
            // playerTurn = 1;
        }
        //turn++;
        // if (turn % 5 == 0) {
        //     for (int i = 0; i < nbMonsters; i++) {
        //         if (monsterTurns[i]) {
        //             int damage = monsters[i]->attack - player->armor->equipmentEffectivenessValue;
        //             if (damage < 0) {
        //                 damage = 0;
        //             }
        //             player->health -= damage;
        //             printf("The %s attacked you for %d damage\n", monsters[i]->name, damage);
        //             if (player->health <= 0) {
        //                 printf("You died !\n");
        //                 exit(0);
        //             }
        //         }
        //     }
        // }
        //printf("This is your weapon : \n", player->weapon->name);

    return;
}