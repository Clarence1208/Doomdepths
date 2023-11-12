#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "MESSAGE_RESOLVER/messageResolver.h"
#include "EQUIPMENT/equipment.h"
#include "INVENTORY/inventory.h"
#include "INVENTORY/inventoryMenu.h"
#include "DATABASE/database.h"
#include "PLAYER/player.h"
#include "LOGGER/logger.h"
#include "MAP/map.h"
#include "UTILS/utils.h"
#include "PLAYER/player.h"

#include <stdio.h>

int main() {
    printf("\n\n\n                                     /\\ \n");
    printf("                                     || \n");
    printf("                       ____ (((\033[1;33m+\033[0m))) _||_ \n");
    printf("                      /.--.\\  .-.  /.||.\\ \n");
    printf("                     /.,   \\\\(\033[1;31m0\033[0m.\033[1;31m0\033[0m)// || \\\\ \n");
    printf("                    /;`\";/\\ \\\\|\033[1;31mm\033[0m|//  ||  ;\\ \n");
    printf("                    |:   \\ \\__`:`____||__:| \n");
    printf("                    |:    \\__ \\\033[1;33mT\033[0m/ (@~)(~@)| \n");
    printf("                    |:    _/|     |\\_\\/  :| \n");
    printf("                    |:   /  |     |  \\   :| \n");
    printf("\033[1;33m______ _____  ________  ________ ___________ _____ _   _  _____ \n");
    printf("|  _  \\  _  ||  _  |  \\/  |  _  \\  ___| ___ \\_   _| | | |/  ___| \n");
    printf("| | | | | | || | | | .  . | | | | |__ | |_/ / | | | |_| |\\ `--. \n");
    printf("| | | | | | || | | | |\\/| | | | |  __||  __/  | | |  _  | `--. \\ \n");
    printf("| |/ /\\ \\_/ /\\ \\_/ / |  | | |/ /| |___| |     | | | | | |/\\__/ / \n");
    printf("|___/  \\___/  \\___/\\_|  |_/___/ \\____/\\_|     \\_/ \\_| |_|\\____/\033[0m \n\n\n\n\n\n\n\n");

    printf("Press any key to start the game...\n");
    system("/bin/stty raw");
    char movement = getchar();
    system("/bin/stty cooked");

    cls();
    printf("What is your name young traveller... (max = 20)\n\n");
    printf("Name >> ");
    char *name = malloc(sizeof(char) * 21);
    scanf("%s", name);

    Player *player = newPlayer(name);

    createMap(player);

    return 0;
}
