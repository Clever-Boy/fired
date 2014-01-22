/***********************************************************************
     * File       : item.cpp
     * Created    : Sep 03, 2013
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#include "game.hpp"



/***********************************************************************
     * InventoryItem
     * constructor

***********************************************************************/
fired::InventoryItem::InventoryItem() {
	base  = NULL;
	count = 0;
}



/***********************************************************************
     * InventoryItem
     * constructor

***********************************************************************/
fired::InventoryItem::InventoryItem(fired::BaseItem *_base, unsigned int _count) {
	base  = _base;
	count = _count;
}



/***********************************************************************
     * InventoryItem
     * render

***********************************************************************/
void fired::InventoryItem::render(sf::Vector2f pos) {
	sf::Sprite *sprite = base->sprite->spr;
	if (sprite == NULL) return;

	sprite->setOrigin(base->sprite->size / 2.0f);
	sprite->setPosition(pos);
	sprite->setRotation(0.0f);
	app->draw(*sprite);
}
