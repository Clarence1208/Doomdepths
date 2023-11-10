//
// Created by Neven Le Gall on 25/10/2023.
//

#include "../EQUIPMENT/equipment.h"
#include "../SPELL/spells.h"
#include "../INVENTORY/inventory.h"
#include "../PLAYER/player.h"
#include "../MONSTER/monster.h"
#include "BDDService/playerService.c"
#include "BDDService/inventoryService.c"
#include "BDDService/equipmentService.c"
#include "BDDService/consumableService.c"
#include "BDDService/spellService.c"
#include "BDDService/monsterService.c"

// Contrôleur CRUD pour la table Player
int createPlayerBDD(sqlite3 *db, Player *player){ return createPlayer(db, player); };
int readPlayerBDD(sqlite3 *db, Player *player){ return readPlayer(db, player);};
int updatePlayerBDD(sqlite3 *db, const Player *player){ return updatePlayer(db, player);};


// Contrôleur CRUD pour la table Inventory
int createInventoryBDD(sqlite3 *db, Inventory *inventory);
int readInventoryBDD(sqlite3 *db, int inventoryId, Inventory *inventory);
int updateInventoryBDD(sqlite3 *db, int inventoryId, const Inventory *inventory);
int deleteInventoryBDD(sqlite3 *db, int inventoryId);

// Contrôleur CRUD pour la table Equipment
int createEquipmentBDD(sqlite3 *db, Equipment *equipment);
int readEquipmentBDD(sqlite3 *db, int equipmentId, Equipment *equipment);
int updateEquipmentBDD(sqlite3 *db, int equipmentId, const Equipment *equipment);
int deleteEquipmentBDD(sqlite3 *db, int equipmentId);

// Contrôleur CRUD pour la table Consumable
int createConsumableBDD(sqlite3 *db, Consumable *consumable);
int readConsumableBDD(sqlite3 *db, int consumableId, Consumable *consumable);
int updateConsumableBDD(sqlite3 *db, int consumableId, const Consumable *consumable);
int deleteConsumableBDD(sqlite3 *db, int consumableId);

// Contrôleur CRUD pour la table Spell
int createSpellBDD(sqlite3 *db, Spell *spell);
int readSpellBDD(sqlite3 *db, int spellId, Spell *spell);
int updateSpellBDD(sqlite3 *db, int spellId, const Spell *spell);
int deleteSpellBDD(sqlite3 *db, int spellId);

// Contrôleur CRUD pour la table Monster
int createMonsterBDD(sqlite3 *db, Monster *monster);
int readMonsterBDD(sqlite3 *db, int monsterId, Monster *monster);
int updateMonsterBDD(sqlite3 *db, int monsterId, const Monster *monster);
int deleteMonsterBDD(sqlite3 *db, int monsterId);
