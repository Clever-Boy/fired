#ifndef __INVENTORY
#define __INVENTORY


#include "map_item.hpp"
#include "item.hpp"
#include "loot_item.hpp"
#include "collectable_item.hpp"


namespace fired {
	struct Inventory {
		fired::Character *owner;

		fired::InventoryItem *items[10][5];
		fired::InventoryItem *credits;

		fired::InventoryItem *helm;
		fired::InventoryItem *body;
		fired::InventoryItem *arms;
		fired::InventoryItem *fist;
		fired::InventoryItem *legs;
		fired::InventoryItem *shoe;

		fired::InventoryItem *primaryWeapon;
		fired::InventoryItem *secondaryWeapon;


		 Inventory(fired::Character *_owner, fired::World *world);
		~Inventory();

		void pickup(fired::InventoryItem *item);
		bool canPickup(fired::InventoryItem *item);
		void dropAll(fired::World *world);
		void generateLoot(std::vector<fired::LootItem*> *_items, fired::World *world);
	};
}

#endif
