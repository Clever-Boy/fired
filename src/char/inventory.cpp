#include "game.hpp"


//======================================================================


fired::Inventory::Inventory(fired::Character *_owner, fired::World *world) {
	owner   = _owner;
	credits = new fired::InventoryItem(itMoney, 0, "credits", world);

	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 5; j++)
			items[i][j] = NULL;
}

//======================================================================


void fired::Inventory::pickup(fired::CollectableItem *item) {
	if (item->item->type == itMoney) {
		credits->count += item->item->count;
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

//======================================================================


void fired::Inventory::dropAll(fired::World *world) {
	float angle;
	sf::Vector2f pos = owner->phys.center;


	if (credits->count > 0) {
		angle = -(random() % 180) * 3.14f / 180.0f;
		world->addItem(credits, pos, sf::Vector2f(ITEM_SPEED * cos(angle), ITEM_SPEED * sin(angle)));
	}


	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 5; j++)
			if (items[i][j] != NULL) {
				angle = -(random() % 180) * 3.14f / 180.0f;
				world->addItem(items[i][j], pos, sf::Vector2f(ITEM_SPEED * cos(angle), ITEM_SPEED * sin(angle)));
			}
}
