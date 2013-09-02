#include "game.hpp"


//======================================================================


fired::Inventory::Inventory(fired::Character *_owner, fired::World *world) {
	owner   = _owner;
	credits = new fired::InventoryItem(itMoney, 0, "credits", world);

	helm = NULL;
	body = NULL;
	arms = NULL;
	fist = NULL;
	legs = NULL;
	shoe = NULL;

	primaryWeapon   = NULL;
	secondaryWeapon = NULL;

	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 5; j++)
			items[i][j] = NULL;
}

//======================================================================


fired::Inventory::~Inventory() {
	if (helm) delete helm;
	if (body) delete body;
	if (arms) delete arms;
	if (fist) delete fist;
	if (legs) delete legs;
	if (shoe) delete shoe;

	if (credits)         delete credits;
	if (primaryWeapon)   delete primaryWeapon;
	if (secondaryWeapon) delete secondaryWeapon;

	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 5; j++)
			if(items[i][j]) delete items[i][j];
}

//======================================================================


void fired::Inventory::pickup(fired::InventoryItem *item) {
	if (item->type == itMoney) {
		credits->count += item->count;
		delete item;
		return;
	}


	if (item->type == itAny)
		for (int i = 0; i < 10; i++)
			for (int j = 0; j < 5; j++)
				if (items[i][j] != NULL)
					if (items[i][j]->type == item->type && !strcmp(items[i][j]->caption, item->caption) && items[i][j]->count != ITEM_MAX_STACK) {
						if (items[i][j]->count + item->count <= ITEM_MAX_STACK) {
							items[i][j]->count += item->count;
							delete item;
							return;
						} else {
							item->count = ITEM_MAX_STACK - items[i][j]->count;
							items[i][j]->count = ITEM_MAX_STACK;
						}
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
		credits = new fired::InventoryItem(itMoney, 0, "credits", world);
	}


	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 5; j++)
			if (items[i][j] != NULL) {
				angle = -(random() % 180) * 3.14f / 180.0f;
				world->addItem(items[i][j], pos, sf::Vector2f(ITEM_SPEED * cos(angle), ITEM_SPEED * sin(angle)));
				items[i][j] = NULL;
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
