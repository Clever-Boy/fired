/***********************************************************************
     * File       : object_collector.cpp
     * Created    : Sep 03, 2013
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#include "game.hpp"



/***********************************************************************
     * BaseMapObjectCollector
     * constructor

***********************************************************************/
fired::BaseMapObjectCollector::BaseMapObjectCollector(unsigned int id, sf::Vector2f _pos) {
	type    = moCollector;
	pos     = _pos;
	decorId = id;
}



/***********************************************************************
     * BaseMapObjectCollector
     * generateLoot

***********************************************************************/
void fired::BaseMapObjectCollector::generateLoot(std::vector<fired::MapLootItem*> *loot) {
	if (loot == NULL) return;


	fired::MapLootItem   *lootItem;
	int                   count;


	for (unsigned int i = 0; i < loot->size(); i++) {
		lootItem = (*loot)[i];
		if (((rand() % 100) / 100.0f) > lootItem->probability) continue;

		count = lootItem->minCount + (rand() % (lootItem->maxCount - lootItem->minCount + 1));
		items.push_back(new fired::MapItem(count, lootItem->items[random() % lootItem->items.size()]));
	}
}



/***********************************************************************
     * BaseMapObjectCollector
     * addItem

***********************************************************************/
void fired::BaseMapObjectCollector::addItem(unsigned int _count, const char *name) {
	items.push_back(new fired::MapItem(_count, container->getItemIndex(name)));
}



/***********************************************************************
     * MapObjectCollector
     * constructor

***********************************************************************/
fired::MapObjectCollector::MapObjectCollector(unsigned int _decorId, sf::Vector2f pos) {
	type    = moCollector;
	decorId = _decorId;
	decor   = new fired::Decor(container->decors[decorId], pos);
}
