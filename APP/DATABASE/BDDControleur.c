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
int createPlayerBDD(Player *player){ return createPlayer(db, player); };
int readPlayerBDD(Player *player){ return readPlayer(db, player);};
int updatePlayerBDD(const Player *player){ return updatePlayer(db, player);};


// Contrôleur CRUD pour la table Inventory
int createInventoryBDD(sqlite3 *db, Inventory *inventory){ return createInventory(db, inventory);};
int readInventoryBDD(sqlite3 *db, Inventory *inventory){ return readInventory(db, inventory);};
int updateInventoryBDD(sqlite3 *db, const Inventory *inventory){ return updateInventory(db, inventory);};

// Contrôleur CRUD pour la table Equipment
int createEquipmentBDD(sqlite3 *db, Equipment *equipment){ return createEquipment(db, equipment);};
int readEquipmentBDD(sqlite3 *db, Equipment *equipment){ return readEquipment(db, equipment);};
int updateEquipmentBDD(sqlite3 *db, const Equipment *equipment){ return updateEquipment(db, equipment);};

// Contrôleur CRUD pour la table Consumable
int createConsumableBDD(sqlite3 *db, Consumable *consumable){ return createConsumablebdd(db, consumable);};
int readConsumableBDD(sqlite3 *db, int consumableId, Consumable *consumable){ return readConsumablebdd(db, consumable);};
int updateConsumableBDD(sqlite3 *db, int consumableId, const Consumable *consumable){ return updateConsumablebdd(db, consumable);};

// Contrôleur CRUD pour la table Spell
int createSpellBDD(sqlite3 *db, Spell *spell){ return createSpellbdd(db, spell);};
int readSpellBDD(sqlite3 *db, int spellId, Spell *spell){ return readSpellbdd(db, spell);};
int updateSpellBDD(sqlite3 *db, int spellId, const Spell *spell){ return updateSpellbdd(db, spell);};

// Contrôleur CRUD pour la table Monster
int createMonsterBDD(sqlite3 *db, Monster *monster){ return createMonsterbdd(db, monster);};
int readMonsterBDD(sqlite3 *db, int monsterId, Monster *monster){ return readMonsterbdd(db, monster);};
int updateMonsterBDD(sqlite3 *db, int monsterId, const Monster *monster){ return updateMonsterbdd(db, monster);};
