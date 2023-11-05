#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "MESSAGE_RESOLVER/messageResolver.h"
#include "EQUIPMENT/equipment.h"
#include "INVENTORY/inventory.h"
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



/*

    sqlite3 *db;
    char *zErrMsg = "failed to open database";
    int rc =  sqlite3_open("doomdepths.db", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 0;
    } else {
        fprintf(stderr, "Opened database successfully\n");
    }
    char *sql = "";
   // createDatabase(db, "", zErrMsg, rc);

    createTableEquipments(db,sql,  zErrMsg, rc);
    insterIntoTest();
*//*


    // Free what's needed to be freed
    freeTranslationList(translationList);
    freeInventory(inventory);*/

    closeLogger();
    return 0;
}