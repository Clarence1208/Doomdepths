cmake_minimum_required(VERSION 3.26)
project(Doomdepths C)

set(CMAKE_C_STANDARD 11)

add_executable(Doomdepths APP/main.c
        APP/PLAYER/player.c
        APP/PLAYER/player.h
        APP/EQUIPMENT/equipment.c
        APP/EQUIPMENT/equipment.h
        APP/SPELL/spell.c
        APP/SPELL/spell.h
        APP/SPELL/spells.c
        APP/SPELL/spells.h
        APP/INVENTORY/inventory.c
        APP/INVENTORY/inventory.h
        APP/CONSUMABLE/consumable.c
        APP/CONSUMABLE/consumable.h
        APP/MESSAGE_RESOLVER/messageResolver.c
        APP/MESSAGE_RESOLVER/messageResolver.h
        APP/MONSTER/monster.c
        APP/MONSTER/monster.h
        APP/DATABASE/database.c
        APP/DATABASE/database.h
        APP/DATABASE/sqlite3.c
        APP/DATABASE/sqlite3.h
        APP/LOGGER/logger.c
        APP/LOGGER/logger.h
        APP/INVENTORY/inventoryMenu.c
        APP/INVENTORY/inventoryMenu.h
        APP/MAP/map.c
        APP/MAP/map.h
        APP/UTILS/utils.c
        APP/UTILS/utils.h
        APP/COMBAT/combat.c
        APP/COMBAT/combat.h
        APP/SHOP/shop.c
        APP/SHOP/shop.h
)
