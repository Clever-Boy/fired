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
void fired::BaseMapObjectCollector::generateLoot() {
	addItem(100, "ammo.bullet");
	addItem(100, "ammo.rocket");
	addItem(100, "ammo.plasma.bolt");
	addItem(50, "ammo.shell");
	addItem(1, "weapon.plasmagun");
	addItem(1, "weapon.bazooka");
	addItem(1, "weapon.shotgun");
	addItem(1, "armor.arms.leather");
	addItem(1, "armor.fist.leather");
	addItem(1, "armor.head.leather");
	addItem(1, "armor.body.leather");
	addItem(1, "armor.legs.leather");
	addItem(1, "armor.shoe.leather");
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
