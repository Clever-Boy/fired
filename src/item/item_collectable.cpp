/***********************************************************************
     * File       : item_collectable.cpp
     * Created    : Sep 03, 2013
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#include "game.hpp"



/***********************************************************************
     * CollectableItem
     * constructor

***********************************************************************/
fired::CollectableItem::CollectableItem(fired::InventoryItem *_item, sf::Vector2f pos, sf::Vector2f velocity, fired::World *_world) {
	item.base  = _item->base;
	item.count = _item->count;
	world = _world;

	phys.size         = sf::Vector2f(8, 8);
	phys.pos          = pos;
	phys.velocity     = velocity;
	phys.acceleration = sf::Vector2f(0, PHYS_GRAVITY / 4);

	phys.isMoving = false;
	phys.onGround = false;
}



/***********************************************************************
     * CollectableItem
     * update

***********************************************************************/
void fired::CollectableItem::update() {
	if (phys.onGround) phys.velocity.x = 0;
	if (world->isRectVisible(phys.rect)) render();
}



/***********************************************************************
     * CollectableItem
     * render

***********************************************************************/
void fired::CollectableItem::render() {
	item.render(phys.pos);
}
