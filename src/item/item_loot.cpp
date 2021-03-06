/***********************************************************************
     * File       : item_loot.cpp
     * Created    : Sep 03, 2013
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#include "game.hpp"



/***********************************************************************
     * LootItem
     * constructor

***********************************************************************/
fired::LootItem::LootItem(unsigned int _minCount, unsigned int _maxCount, float _probability) {
	minCount    = _minCount;
	maxCount    = _maxCount;
	probability = _probability;
}



/***********************************************************************
     * LootItem
     * addItem

***********************************************************************/
void fired::LootItem::addItem(fired::BaseItem *item) {
	items.push_back(item);
}



/***********************************************************************
     * MapLootItem
     * constructor

***********************************************************************/
fired::MapLootItem::MapLootItem(const char *__items, unsigned int _minCount, unsigned int _maxCount, float _probability) {
	char _items[256];
	memset(_items, 0, sizeof(_items));
	strncpy(_items, __items, sizeof(_items));

	char *token = strtok(_items, "|");
		while (token) {
			items.push_back(container->getItemIndex(token));
			token = strtok(NULL, "|");
		}

	minCount    = _minCount;
	maxCount    = _maxCount;
	probability = _probability;
}
