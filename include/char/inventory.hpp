#ifndef __INVENTORY
#define __INVENTORY

namespace fired {
	struct Inventory {
		fired::Character *owner;

		unsigned long credits;


		 Inventory(fired::Character *_owner);
		~Inventory() {};
	};
}

#endif
