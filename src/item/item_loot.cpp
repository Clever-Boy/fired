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
fired::LootItem::LootItem(fired::BaseItem *_base, unsigned int _minCount, unsigned int _maxCount, float _probability) {
	base        = _base;
	minCount    = _minCount;
	maxCount    = _maxCount;
	probability = _probability;
}
