#ifndef __INVENTORY
#define __INVENTORY


#include "item.hpp"


namespace fired {
	struct Inventory {
		fired::Character *owner;

		fired::BaseInventoryItem *items[10][5];
		unsigned long credits;


		 Inventory(fired::Character *_owner);
		~Inventory() {};
	};
}

#endif
