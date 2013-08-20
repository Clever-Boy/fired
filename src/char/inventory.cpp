#include "game.hpp"


//======================================================================


fired::Inventory::Inventory(fired::Character *_owner) {
	owner   = _owner;
	credits = 0;

	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 5; j++)
			items[i][j] = NULL;
}

//======================================================================


void fired::Inventory::pickup(fired::CollectableItem *item) {
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 5; j++)
			if (items[i][j] == NULL)
				items[i][j] = item->item;
}

//======================================================================


bool fired::Inventory::canPickup() {
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 5; j++)
			if (items[i][j] == NULL)
				return true;

	return false;
}
