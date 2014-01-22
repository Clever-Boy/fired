/***********************************************************************
     * File       : inventory.hpp
     * Created    : Sep 03, 2013
     * Copyright  : (C) 2013 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#ifndef __INVENTORY
#define __INVENTORY


#include "map_item.hpp"
#include "item.hpp"
#include "loot_item.hpp"
#include "collectable_item.hpp"


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

		int credits;


		Inventory(fired::Character *_owner);

		void pickup(fired::InventoryItem *item);
		bool canPickup(fired::InventoryItem *item);
		void dropAll(fired::World *world);
		void generateLoot(std::vector<fired::LootItem*> *_items);
	};
}

#endif
