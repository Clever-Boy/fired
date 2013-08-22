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


void fired::Inventory::pickup(fired::InventoryItem *item) {
	if (item->type == itMoney) {
		credits->count += item->count;
		delete item;
		return;
	}


	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 5; j++)
			if (items[i][j] != NULL)
				if (items[i][j]->type == item->type && !strcmp(items[i][j]->caption, item->caption)) {
					items[i][j]->count += item->count;
					delete item;
					return;
				}


	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 5; j++)
			if (items[i][j] == NULL) {
				items[i][j] = item;
				return;
			}
}

//======================================================================


bool fired::Inventory::canPickup(fired::InventoryItem *item) {
	if (item->type == itMoney) return true;

	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 5; j++)
			if ((items[i][j] == NULL) || (items[i][j]->type == item->type && !strcmp(items[i][j]->caption, item->caption)))
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

//======================================================================


void fired::Inventory::generateLoot(std::vector<fired::LootItem*> *_items, fired::World *world) {
	fired::LootItem      *lootItem;
	fired::InventoryItem *item;
	int                   count;


	for (unsigned int i = 0; i < _items->size(); i++) {
		lootItem = (*_items)[i];

		if (((random() % 100) / 100.0f) > lootItem->probability) continue;
		count = lootItem->minCount + (random() % (lootItem->maxCount - lootItem->minCount + 1));
		item = new fired::InventoryItem(lootItem->type, count, lootItem->name, world);
		if (canPickup(item)) pickup(item);
		else delete item;
	}
}
