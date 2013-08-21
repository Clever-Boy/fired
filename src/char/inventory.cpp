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
	if (item->item->type == itMoney) {
		credits += item->item->count;
		delete item->item;
		return;
	}


	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 5; j++)
			if (items[i][j] != NULL)
				if (items[i][j]->type == item->item->type && !strcmp(items[i][j]->caption, item->item->caption)) {
					items[i][j]->count += item->item->count;
					delete item->item;
					return;
				}


	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 5; j++)
			if (items[i][j] == NULL) {
				items[i][j] = item->item;
				return;
			}
}

//======================================================================


bool fired::Inventory::canPickup(fired::CollectableItem *item) {
	if (item->item->type == itMoney) return true;

	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 5; j++)
			if ((items[i][j] == NULL) || (items[i][j]->type == item->item->type && !strcmp(items[i][j]->caption, item->item->caption)))
				return true;

	return false;
}
