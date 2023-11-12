//
// Created by Neven Le Gall on 25/10/2023.
//

#ifndef DOOMDEPTHS_DATABASE_H
#define DOOMDEPTHS_DATABASE_H

#include "../EQUIPMENT/equipment.h"
#include "../SPELL/spells.h"
#include "../INVENTORY/inventory.h"
#include "../PLAYER/player.h"
#include "../MONSTER/monster.h"

// Contrôleur CRUD pour la table Player
int createPlayerBDD(Player *player);
int readPlayerBDD(int playerId, Player *player);
int updatePlayerBDD(int playerId, const Player *player);

// Contrôleur CRUD pour la table Inventory
int createInventoryBDD(Inventory *inventory);
int readInventoryBDD(int inventoryId, Inventory *inventory);
int updateInventoryBDD(int inventoryId, const Inventory *inventory);
int deleteInventoryBDD(int inventoryId);

// Contrôleur CRUD pour la table Equipment
int createEquipmentBDD(Equipment *equipment);
int readEquipmentBDD(int equipmentId, Equipment *equipment);
int updateEquipmentBDD(int equipmentId, const Equipment *equipment);
int deleteEquipmentBDD(int equipmentId);

// Contrôleur CRUD pour la table Consumable
int createConsumableBDD(Consumable *consumable);
int readConsumableBDD(int consumableId, Consumable *consumable);
int updateConsumableBDD(int consumableId, const Consumable *consumable);
int deleteConsumableBDD(int consumableId);

// Contrôleur CRUD pour la table Spell
int createSpellBDD(Spell *spell);
int readSpellBDD(int spellId, Spell *spell);
int updateSpellBDD(int spellId, const Spell *spell);
int deleteSpellBDD(int spellId);

// Contrôleur CRUD pour la table Spells
int createSpellsBDD(Spells *spells);
int readSpellsBDD(int playerId, Spells *spells);
int updateSpellsBDD(int playerId, const Spells *spells);
int deleteSpellsBDD(int playerId);

// Contrôleur CRUD pour la table Monster
int createMonsterBDD(Monster *monster);
int readMonsterBDD(int monsterId, Monster *monster);
int updateMonsterBDD(int monsterId, const Monster *monster);
int deleteMonsterBDD(int monsterId);

//controleur CRUD pour la map
int createMapBDD(Map *map);
int readMapBDD(Map *map);
int updateMapBDD(const Map *map);


#endif //DOOMDEPTHS_DATABASE_H