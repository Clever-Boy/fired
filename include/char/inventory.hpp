#ifndef __INVENTORY
#define __INVENTORY


#include "item.hpp"


namespace fired {
	struct Inventory {
		fired::Character *owner;

		fired::InventoryItem *items[10][5];
		unsigned long credits;


		 Inventory(fired::Character *_owner);
		~Inventory() {};

		void pickup(fired::CollectableItem *item);
		bool canPickup();
	};
}

#endif
