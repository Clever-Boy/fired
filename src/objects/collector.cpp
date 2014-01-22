/***********************************************************************
     * File       : collector.cpp
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
fired::BaseMapObjectCollector::BaseMapObjectCollector(const char *_name, sf::Vector2f _pos) {
	type = moCollector;
	pos  = _pos;

	strncpy(decorName, _name, sizeof(decorName));
}



/***********************************************************************
     * BaseMapObjectCollector
     * generateLoot

***********************************************************************/
void fired::BaseMapObjectCollector::generateLoot() {
	addItem(1, "weapon.plasmagun");
	addItem(1, "armor.body.leather");
}



/***********************************************************************
     * BaseMapObjectCollector
     * addItem

***********************************************************************/
void fired::BaseMapObjectCollector::addItem(unsigned int _count, const char *_name) {
	items.push_back(new fired::MapItem(_count, _name));
}



/***********************************************************************
     * MapObjectCollector
     * constructor

***********************************************************************/
fired::MapObjectCollector::MapObjectCollector(fired::Decor *_decor) {
	type = moCollector;
	decor = _decor;
}
