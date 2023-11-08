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
        player->experience += monsters[choice]->experience * experienceSpell;
        player->gold += monsters[choice]->gold * moneySpell;
        printf("You gained %d experience !\n", (monsters[choice]->experience * experienceSpell));
        printf("You gained %d gold !\n", (monsters[choice]->gold * moneySpell));
        popMonster(monsters, choice, *nbMonsters);
        (*nbMonsters)--;
        if (*nbMonsters == 0) {
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
        printf("THIS IS THE BOSS OF THIS AREA !!!\n");
        printf("Be careful, he is very strong !\n\n");
        printf("Kill him to get to the next area !\n\n");
        monsters = malloc(sizeof(Monster**));
        monsters[0] = createBoss(player);
        nbMonsters = 1;
        monsterToFree = 1;
        printf("You are getting attacked by a %s !\n", monsters[0]->name);
    } else {
        nbMonsters = rand() % 3 + 1;
        monsterToFree = nbMonsters;
        srand(time(NULL));
        monsters = malloc(sizeof(Monster**) * nbMonsters);
        for (int i = 0; i < nbMonsters; i++) {
            monsters[i] = createMonster(player);
            printf("You are getting attacked by a %s !\n", monsters[i]->name);
        }
    }

    printf("\n");

    // TODO: Create monsters in terminal

    int turn = 0;
    int playerTurn = 1;
    int monsterTurn = 0;
    int moneySpell = 1;
    int experienceSpell = 1;
    while (1) {
        if (playerTurn) {
            printf("It's your turn !\n");
            char input = '0';
            while (input != 'a' && input != 's' && input != 'p') {
                printf("Press 'a' to attack, 's' to use a spell or 'e' to use your inventory\n");
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
                        cls();
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
                        // TO DO : Free monsters and spells
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
                int findSpell = 0;
                for (int i = 0; i < nbSpells; i++) {
                    if (spells[i]->levelToUnlock <= player->level) {
                        findSpell++;
                    }
                    if (findSpell == choice) {
                        if (player->mana >= spells[i]->manaCost) {
                            if (spells[i]->type == Fireball) {
                                int choice = 0;
                                while(choice < 1 || choice > nbMonsters) {
                                    cls();
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
                                int isOver = damageMonster(monsters, spells[i]->spellEffectivenessValue + player->level, choice-1, &nbMonsters, player, isBoss, moneySpell, experienceSpell);
                                if (isOver) {
                                    // TO DO : Free monsters and spells
                                    // free(monsters);
                                    // free(spells);
                                    return;
                                }
                            } else if (spells[i]->type == Bang) {
                                for (int k = nbMonsters-1; k >= 0; k--) {
                                    int isOver = damageMonster(monsters, spells[i]->spellEffectivenessValue + player->level, k, &nbMonsters, player, isBoss, moneySpell, experienceSpell);
                                    if (isOver) {
                                        // TO DO : Free monsters and spells
                                        // free(monsters);
                                        // free(spells);
                                        return;
                                    }
                                }
                            } else if (spells[i]->type == Heal) {
                                player->health += spells[i]->spellEffectivenessValue + player->level;
                                if (player->health > player->max_health) {
                                    player->health = player->max_health;
                                }
                                cls();
                                printf("You healed yourself for %d health\n", spells[i]->spellEffectivenessValue + player->level);
                                printf("\nPress any key to continue...\n");
                                system("/bin/stty raw");
                                char wait = getchar();
                                system("/bin/stty cooked");
                            } else if (spells[i]->type == Mana) {
                                player->mana += spells[i]->spellEffectivenessValue + player->level;
                                if (player->mana > player->max_mana) {
                                    player->mana = player->max_mana;
                                }
                                cls();
                                printf("You regenerated %d mana\n", spells[i]->spellEffectivenessValue + player->level);
                                printf("\nPress any key to continue...\n");
                                system("/bin/stty raw");
                                char wait = getchar();
                                system("/bin/stty cooked");
                            } else if (spells[i]->type == Money) {
                                cls();
                                moneySpell = 2;
                                printf("You used the spell Money Rain !\n");
                                printf("The monsters will drop more gold !\n");
                                printf("\nPress any key to continue...\n");
                                system("/bin/stty raw");
                                char wait = getchar();
                                system("/bin/stty cooked");
                            } else if (spells[i]->type == Experience) {
                                cls();
                                experienceSpell = 2;
                                printf("You used the spell Experience Rain !\n");
                                printf("The monsters will drop more experience !\n");
                                printf("\nPress any key to continue...\n");
                                system("/bin/stty raw");
                                char wait = getchar();
                                system("/bin/stty cooked");
                            }
                            player->mana -= spells[i]->manaCost;
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
            } else {
                // TO DO : Inventory
            }
        } else if (monsterTurn) {
            cls();
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