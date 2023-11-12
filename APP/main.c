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


int main() {

    initLogger("../APP/app.log");

//    logMessage(DEBUG, "This is a debug message: %d", 42);
//    logMessage(INFO, "This is an informational message: %s", "Hello, world!");
//    logMessage(ERROR, "This is an error message: %s", "Something went wrong!");




    Player * player = newPlayer("test", FR);

    printf("%s",player->name);

    printWeapon(player);



    // Load the appropriate language file (e.g., "strings_fr.txt" or "strings_en.txt")
    TranslationList* translationList = loadTranslations("../TEXT/message-en.env");

    // Set the currently selected language (e.g., based on user preference)

    // Use the translate function to display translated text
    const char *playText = translate("play", translationList);
    const char *quitText = translate("quit", translationList);
    const char *welcomeText = translate("welcome_message", translationList);

    printf("%s\n%s\n%s\n", playText, quitText, welcomeText);

    translationList = loadTranslations("../TEXT/message-fr.env");

    printf("\n\n%s\n%s\n%s\n"
            , translate("play", translationList)
            , translate("quit", translationList)
            , translate("welcome_message", translationList));

    Equipment *equipment = createDefaultWeapon();

    printEquipment(*equipment, translationList);

    Equipment *equipment2 = createDefaultArmor();

    printEquipment(*equipment2, translationList);

    Equipment *equipment3 = createEquipment("name", "description", 10, 100, 100, 100, WEAPON);

    printEquipment(*equipment3, translationList);

    Inventory * inventory = create_inventory(10);
    printInventory(inventory, translationList);

    addEquipmentToInventory(inventory, *equipment);
    printInventory(inventory, translationList);

    addEquipmentToInventory(inventory, *equipment);
    addEquipmentToInventory(inventory, *equipment2);
    addEquipmentToInventory(inventory, *equipment3);

    addEquipmentToPlayerInventory(player, *equipment);
    addEquipmentToPlayerInventory(player, *equipment2);
    addEquipmentToPlayerInventory(player, *equipment3);

    Consumable *consumable = createRandomConsumableOfType(1);
    addConsumableToPlayerInventory(player, *consumable);

    Consumable *consumable2 = createRandomConsumable();
    addConsumableToPlayerInventory(player, *consumable2);
    addConsumableToPlayerInventory(player, *consumable2);
    addConsumableToPlayerInventory(player, *consumable2);
    addConsumableToPlayerInventory(player, *consumable2);
    addConsumableToPlayerInventory(player, *consumable2);
    addConsumableToPlayerInventory(player, *consumable2);

    printConsumable(consumable);
    printConsumable(consumable2);

    printConsumable(&player->inventory->consumable[0]);


    player->health = 50;
    player->mana = 50;


    Equipment *equipment4 = createEquipment("test", "description", 10, 100, 100, 100, WEAPON);
    addEquipmentToPlayerInventoryMenu(player, *equipment4);

    selectableItemInventoryMenu(player);

    printf("health : %d\n", player->health);
    printf("mana : %d\n", player->mana);



    printf("inventory size : %d\n", player->inventory->size);
    printf("inventory max size : %d\n", player->inventory->max_size);
    printf("inventory nbr equipment : %d\n", player->inventory->nbrEquipment);
    printf("inventory nbr consumable : %d\n", player->inventory->nbrConsumable);

    printf("inventory size : %d\n", inventory->size);
    printf("inventory max size : %d\n", inventory->max_size);
    printf("inventory nbr equipment : %d\n", inventory->nbrEquipment);
    printf("inventory nbr consumable : %d\n", inventory->nbrConsumable);

    addEquipmentToInventory(player->inventory, *equipment);

//
//    // Free what's needed to be freed
//    freeTranslationList(translationList);
//    freeInventory(inventory);

    closeLogger();
    return 0;
}