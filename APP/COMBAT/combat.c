// Creation date: 05-11-2023
// Author: Nino PLANE
// Last modified: 08-11-2023

#include "stdlib.h"
#include "math.h"
#include "time.h"
#include "combat.h"
#include "../PLAYER/player.h"
#include "../MAP/map.h"
#include "../UTILS/utils.h"
#include "../MONSTER/monster.h"
#include "../SPELL/spell.h"
#include "../INVENTORY/inventoryMenu.h"

void printHUD(Player *player, Monster **monsters, int nbMonsters) {

    printf("PV   : %d / %d : ", player->health, player->max_health);
    for (int i = 0; i < 50; i++) {
        if (i < (player->health * 50 / player->max_health)) {
            printf("\033[1;32m%c\033[0m", '#');
        } else {
            printf("#");
        }
    }

    printf("\n");

    printf("\nMana : %d / %d : ", player->mana, player->max_mana);
    for (int i = 0; i < 50; i++) {
        if (i < (player->mana * 50 / player->max_mana)) {
            printf("\033[1;34m%c\033[0m", '#');
        } else {
            printf("#");
        }
    }

    printf("\n\n");

    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < nbMonsters; j++) {
            printf("%s", monsters[j]->sprite[i]);
        }
        printf("\n");
    }
    printf("\n\n");
}

void popMonster(Monster **monsters, int index, int nbMonsters) {
    freeMonster(monsters[index]);
    for (int i = index; i < nbMonsters - 1; i++) {
        monsters[i] = monsters[i+1];
    }
}

int damageMonster(Monster **monsters, int damage, int choice, int *nbMonsters, Player *player, int isBoss, int moneySpell, int experienceSpell) {
    monsters[choice]->hp -= damage;
    printf("You attacked the %s for %d damage\n", monsters[choice]->name, damage);
    if (monsters[choice]->hp <= 0) {
        printf("\nYou killed the %s !\n", monsters[choice]->name);
        addExperience(player,  monsters[choice]->experience * experienceSpell);
        player->gold += monsters[choice]->gold * moneySpell;
        printf("You gained %d experience !\n", (monsters[choice]->experience * experienceSpell));
        printf("You gained %d gold !\n", (monsters[choice]->gold * moneySpell));
        popMonster(monsters, choice, *nbMonsters);
        (*nbMonsters)--;
        if (*nbMonsters == 0) {
            free(monsters);
            printf("\nYou won the battle !\n");
            if (isBoss) {
                printf("You are now is the new area !\n");
                printf("Careful, the monsters are stronger here !\n");
                player->map_level++;
            }
            printf("\nPress any key to continue...\n");
            system("/bin/stty raw");
            char wait = getchar();
            system("/bin/stty cooked");
            return 1;
        }
    }
    printf("\nPress any key to continue...\n");
    system("/bin/stty raw");
    char wait = getchar();
    system("/bin/stty cooked");
    cls();
    return 0;
}

void startBattle(Player *player, int isBoss) {
    cls();
    int nbMonsters = 0;
    int monsterToFree = 0;
    Monster **monsters = NULL;
    Spell **spells = loadSpells();
    if (isBoss) {
        monsters = malloc(sizeof(Monster**) * 1);
        monsters[0] = createBoss(player);
        nbMonsters = 1;
        monsterToFree = 1;
    } else {
        nbMonsters = rand() % 3 + 1;
        monsterToFree = nbMonsters;
        srand(time(NULL));
        monsters = malloc(sizeof(Monster**) * nbMonsters);
        for (int i = 0; i < nbMonsters; i++) {
            monsters[i] = createMonster(player);
        }
    }

    printHUD(player, monsters, nbMonsters);

    if (isBoss) {
        printf("THIS IS THE BOSS OF THIS AREA !!!\n");
        printf("Be careful, he is very strong !\n\n");
        printf("Kill him to get to the next area !\n\n");
    }

    for (int i = 0; i < nbMonsters; i++) {
        if (isBoss) {
            printf("You are getting attacked by the %s !\n", monsters[i]->name);
        } else {
            printf("You are getting attacked by a %s !\n", monsters[i]->name);
        }
    }
    

    printf("\nPress any key to continue...\n");
    system("/bin/stty raw");
    char wait = getchar();
    system("/bin/stty cooked");
    cls();

    int turn = 0;
    int playerTurn = 1;
    int monsterTurn = 0;
    int moneySpell = 1;
    int experienceSpell = 1;
    while (1) {
        if (playerTurn) {
            cls();
            printHUD(player, monsters, nbMonsters);
            printf("It's your turn !\n");
            char input = '0';
            do{
                printf("Press 'a' to attack, 's' to use a spell or 'e' to use your inventory\n");
                system("/bin/stty raw");
                input = getchar();
                system("/bin/stty cooked");
            } while (input != 'a' && input != 's' && input != 'p' && input != 'e');
            if (input == 'a') {
                int amountAttack = 1;
                if (player->weapon != NULL) {
                    amountAttack = player->weapon->nbAttack;
                }
                while(amountAttack > 0) {
                    int choice = 0;
                    while(choice < 1 || choice > nbMonsters) {
                        cls();
                        printHUD(player, monsters, nbMonsters);
                        printf("You have %d attacks left\n", amountAttack);
                        printf("Choose a monster to attack : \n");
                        for(int k = 0; k < nbMonsters; k++) {
                            printf("%d : %s\n", k+1, monsters[k]->name);
                        }
                        system("/bin/stty raw");
                        input = getchar();
                        system("/bin/stty cooked");
                        choice = input - '0';
                    }
                    cls();
                    printHUD(player, monsters, nbMonsters);
                    int damage = 0;
                    if (player->weapon != NULL) {
                        damage = player->attack + player->weapon->equipmentEffectivenessValue - monsters[choice-1]->defense;
                    } else {
                        damage = player->attack - monsters[choice-1]->defense;
                    }
                    if (damage < 0) {
                        damage = 0;
                    }
                    int isOver = damageMonster(monsters, damage, choice-1, &nbMonsters, player, isBoss, moneySpell, experienceSpell);
                    if (isOver) {
                        // TODO : Free monsters and spells
                        // free(monsters);
                        // free(spells);
                        return;
                    }
                    amountAttack--;
                }
                playerTurn = 0;
                monsterTurn = 1;
            } else if (input == 's') {
                int nbSpells = 9;
                int choice = 0;
                int nbUsableSpells = 0;
                for (int i = 0; i < nbSpells; i++) {
                    if (spells[i]->levelToUnlock <= player->level) {
                        nbUsableSpells++;
                    }
                }
                while(choice < 1 || choice > nbUsableSpells) {
                    cls();
                    printHUD(player, monsters, nbMonsters);
                    int count = 0;
                    printf("Choose a spell to use or 'h' to see spells infos : \n\n");
                    for(int k = 0; k < nbSpells; k++) {
                        if (spells[k]->levelToUnlock <= player->level) {
                            count++;
                            printf("%d : %s - %d\n", count, spells[k]->name, spells[k]->manaCost);
                        } else {
                            printf("XXXXXXXXXXXXXX - (Unlock at level %d !)\n", spells[k]->levelToUnlock);
                        }
                    }
                    system("/bin/stty raw");
                    input = getchar();
                    system("/bin/stty cooked");
                    if (input == 'h') {
                        cls();
                        printHUD(player, monsters, nbMonsters);
                        printf("Spells infos :\n\n");
                        for(int k = 0; k < nbSpells; k++) {
                            if (spells[k]->levelToUnlock <= player->level) {
                                printf("%s : %s\n", spells[k]->name, spells[k]->description);
                            } else {
                                printf("XXXXXXXXXXXXXX : (Unlock at level %d !)\n", spells[k]->levelToUnlock);
                            }
                        }
                        printf("\nPress any key to continue...\n");
                        system("/bin/stty raw");
                        char wait = getchar();
                        system("/bin/stty cooked");
                    }
                    choice = input - '0';
                }
                cls();
                printHUD(player, monsters, nbMonsters);
                int findSpell = 0;
                for (int i = 0; i < nbSpells; i++) {
                    if (spells[i]->levelToUnlock <= player->level) {
                        findSpell++;
                    }
                    if (findSpell == choice) {
                        if (player->mana >= spells[i]->manaCost) {
                            if (spells[i]->type == Fireball) {
                                player->mana -= spells[i]->manaCost;
                                int choice = 0;
                                while(choice < 1 || choice > nbMonsters) {
                                    cls();
                                    printHUD(player, monsters, nbMonsters);
                                    printf("Choose a monster to attack : \n");
                                    for(int k = 0; k < nbMonsters; k++) {
                                        printf("%d : %s\n", k+1, monsters[k]->name);
                                    }
                                    system("/bin/stty raw");
                                    input = getchar();
                                    system("/bin/stty cooked");
                                    choice = input - '0';
                                }
                                cls();
                                printHUD(player, monsters, nbMonsters);
                                int isOver = damageMonster(monsters, spells[i]->spellEffectivenessValue + player->level, choice-1, &nbMonsters, player, isBoss, moneySpell, experienceSpell);
                                if (isOver) {
                                    // TO DO : Free monsters and spells
                                    // free(monsters);
                                    // free(spells);
                                    return;
                                }
                            } else if (spells[i]->type == Bang) {
                                player->mana -= spells[i]->manaCost;
                                for (int k = nbMonsters-1; k >= 0; k--) {
                                    cls();
                                    printHUD(player, monsters, nbMonsters);
                                    int isOver = damageMonster(monsters, spells[i]->spellEffectivenessValue + player->level, k, &nbMonsters, player, isBoss, moneySpell, experienceSpell);
                                    if (isOver) {
                                        // TO DO : Free monsters and spells
                                        // free(monsters);
                                        // free(spells);
                                        return;
                                    }
                                }
                            } else if (spells[i]->type == Heal) {
                                player->mana -= spells[i]->manaCost;
                                player->health += spells[i]->spellEffectivenessValue + player->level;
                                if (player->health > player->max_health) {
                                    player->health = player->max_health;
                                }
                                cls();
                                printHUD(player, monsters, nbMonsters);
                                printf("You healed yourself for %d health\n", spells[i]->spellEffectivenessValue + player->level);
                                printf("\nPress any key to continue...\n");
                                system("/bin/stty raw");
                                char wait = getchar();
                                system("/bin/stty cooked");
                            } else if (spells[i]->type == Mana) {
                                player->mana -= spells[i]->manaCost;
                                player->mana += spells[i]->spellEffectivenessValue + player->level;
                                if (player->mana > player->max_mana) {
                                    player->mana = player->max_mana;
                                }
                                cls();
                                printHUD(player, monsters, nbMonsters);
                                printf("You regenerated %d mana\n", spells[i]->spellEffectivenessValue + player->level);
                                printf("\nPress any key to continue...\n");
                                system("/bin/stty raw");
                                char wait = getchar();
                                system("/bin/stty cooked");
                            } else if (spells[i]->type == Money) {
                                player->mana -= spells[i]->manaCost;
                                cls();
                                printHUD(player, monsters, nbMonsters);
                                moneySpell = 2;
                                printf("You used the spell Money Rain !\n");
                                printf("The monsters will drop more gold !\n");
                                printf("\nPress any key to continue...\n");
                                system("/bin/stty raw");
                                char wait = getchar();
                                system("/bin/stty cooked");
                            } else if (spells[i]->type == Experience) {
                                player->mana -= spells[i]->manaCost;
                                cls();
                                printHUD(player, monsters, nbMonsters);
                                experienceSpell = 2;
                                printf("You used the spell Experience Rain !\n");
                                printf("The monsters will drop more experience !\n");
                                printf("\nPress any key to continue...\n");
                                system("/bin/stty raw");
                                char wait = getchar();
                                system("/bin/stty cooked");
                            }
                            playerTurn = 0;
                            monsterTurn = 1;
                            findSpell++;
                        } else {
                            printf("You don't have enough mana !\n");
                            printf("\nPress any key to continue...\n");
                            system("/bin/stty raw");
                            char wait = getchar();
                            system("/bin/stty cooked");
                        }
                    }
                }
            } else if (input == 'e') {
                selectableItemInventoryMenu(player);
            }
        } else if (monsterTurn) {
            cls();
            printHUD(player, monsters, nbMonsters);
            printf("It's the monster's turn !\n\n");

            for (int i = 0; i < nbMonsters; i++) {
                int damage = 0;
                if(player->armor != NULL) {
                    damage = monsters[i]->attack - player->armor->equipmentEffectivenessValue;
                } else {
                    damage = monsters[i]->attack;
                }
                if (damage < 0) {
                    damage = 0;
                }
                player->health -= damage;
                printf("The %s attacked you for %d damage\n", monsters[i]->name, damage);
                if (player->health <= 0) {
                    printf("\nYou died !\n");
                    printf("      GAME OVER\n");
                    printf("  ---------------\n");
                    printf("  |             |\n");
                    printf("  |    R.I.P    |\n");
                    printf("  |             |\n");
                    printf("  |   LOOSER!   |\n");
                    printf("  |             |\n");
                    printf("  ---------------\n");
                    printf("\nPress any key to continue...\n");
                    system("/bin/stty raw");
                    char wait = getchar();
                    system("/bin/stty cooked");
                    free(monsters);
                    freePlayer(player);
                    return;
                }
            }

            printf("\nPress any key to continue...\n");
            system("/bin/stty raw");
            char wait = getchar();
            system("/bin/stty cooked");
            cls();

            playerTurn = 1;
            monsterTurn = 0;
        }
    }
    return;
}