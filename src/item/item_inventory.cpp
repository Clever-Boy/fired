/***********************************************************************
     * File       : item_inventory.cpp
     * Created    : Sep 03, 2013
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#include "game.hpp"



/***********************************************************************
     * Inventory
     * constructor

***********************************************************************/
fired::Inventory::Inventory(fired::Character *_owner) {
	owner        = _owner;
	credits      = 0;
}



/***********************************************************************
     * Inventory
     * pickup

***********************************************************************/
void fired::Inventory::pickup(fired::InventoryItem *item) {
	for (int i = 0; i < 10; i++) for (int j = 0; j < 5; j++) if (items[i][j].base)
		if ((items[i][j].base->type == item->base->type) && (items[i][j].base->UID == item->base->UID) && (items[i][j].count < items[i][j].base->maxStack)) {
			if (items[i][j].count + item->count <= items[i][j].base->maxStack) {
				items[i][j].count += item->count;
				emptyItem(item);
				return;
			} else {
				unsigned int diffCount = items[i][j].base->maxStack - items[i][j].count;
				items[i][j].count += diffCount;
				item->count       -= diffCount;
			}
		}

	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 5; j++)
			if (items[i][j].base == NULL) {
				items[i][j].base  = item->base;
				items[i][j].count = item->count;
				emptyItem(item);
				return;
			}
}



/***********************************************************************
     * Inventory
     * canPickup

***********************************************************************/
bool fired::Inventory::canPickup(fired::InventoryItem *item) {
	for (int i = 0; i < 10; i++) for (int j = 0; j < 5; j++)
		if (items[i][j].base == NULL)
			return true;
		else if ((items[i][j].base->type == item->base->type) && (items[i][j].base->UID == item->base->UID) && (items[i][j].count < items[i][j].base->maxStack))
			return true;

	return false;
}



/***********************************************************************
     * Inventory
     * dropAll

***********************************************************************/
void fired::Inventory::dropAll(fired::World *world) {
	float angle;
	sf::Vector2f pos = owner->phys.center;

	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 5; j++)
			if (items[i][j].base != NULL) {
				angle = -(rand() % 180) * 3.14f / 180.0f;
				world->addItem(&items[i][j], pos, sf::Vector2f(ITEM_SPEED * cos(angle), ITEM_SPEED * sin(angle)));
				emptyItem(&items[i][j]);
			}
}



/***********************************************************************
     * Inventory
     * generateLoot

***********************************************************************/
void fired::Inventory::generateLoot(std::vector<fired::LootItem*> *_items) {
	fired::LootItem      *lootItem;
	fired::InventoryItem *item;
	int                   count;


	for (unsigned int i = 0; i < _items->size(); i++) {
		lootItem = (*_items)[i];
		if (((rand() % 100) / 100.0f) > lootItem->probability) continue;

		count = lootItem->minCount + (rand() % (lootItem->maxCount - lootItem->minCount + 1));
		item = new fired::InventoryItem(lootItem->items[rand() % lootItem->items.size()], count);

		if (canPickup(item)) pickup(item);
		delete item;
	}
}
