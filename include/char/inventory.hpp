#ifndef __INVENTORY
#define __INVENTORY


#include "item.hpp"


namespace fired {
	struct Inventory {
		fired::Character *owner;

		fired::InventoryItem *items[10][5];
		fired::InventoryItem *credits;


		 Inventory(fired::Character *_owner, fired::World *world);
		~Inventory() {};

		void pickup(fired::InventoryItem *item);
		bool canPickup(fired::InventoryItem *item);
		void dropAll(fired::World *world);
		void generateLoot(std::vector<fired::LootItem*> *_items, fired::World *world);
	};
}

#endif
