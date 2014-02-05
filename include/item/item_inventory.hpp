/***********************************************************************
     * File       : item_inventory.hpp
     * Created    : Sep 03, 2013
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#ifndef __ITEM_INVENTORY
#define __ITEM_INVENTORY


#include "item_map.hpp"
#include "item_base.hpp"
#include "item_loot.hpp"
#include "item_collectable.hpp"


namespace fired {
	struct Inventory {
		fired::Character *owner;
		fired::InventoryItem items[10][5];

		fired::InventoryItem helm;
		fired::InventoryItem body;
		fired::InventoryItem arms;
		fired::InventoryItem fist;
		fired::InventoryItem legs;
		fired::InventoryItem shoe;

		fired::InventoryItem primaryWeapon;
		fired::InventoryItem secondaryWeapon;

		fired::InventoryItem trash;
		int credits;


		Inventory(fired::Character *_owner);

		void pickup(fired::InventoryItem *item);
		bool canPickup(fired::InventoryItem *item);
		void dropAll(fired::World *world);
		void generateLoot(std::vector<fired::LootItem*> *_items);
	};
}

#endif
