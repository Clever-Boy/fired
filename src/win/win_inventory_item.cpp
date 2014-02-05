/***********************************************************************
     * File       : win_inventory_item.cpp
     * Created    : Jan 23, 2014
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#include "game.hpp"



/***********************************************************************
     * InventoryWindowItem
     * constructor

***********************************************************************/
fired::InventoryWindowItem::InventoryWindowItem(sf::Vector2f pos, fired::InventoryItem *_item, fired::ItemType _filter, fired::ArmorClass _armorFilter) {
	item        = _item;
	filter      = _filter;
	armorFilter = _armorFilter;
	rect        = sf::FloatRect(pos, sf::Vector2f(35.0f, 35.0f));
}



/***********************************************************************
     * InventoryWindowItem
     * render

***********************************************************************/
void fired::InventoryWindowItem::render(sf::Sprite *spr, sf::Text *count) {
	spr->setPosition(rectCenter(rect));
	app->draw(*spr);

	renderItem(count);
}



/***********************************************************************
     * InventoryWindowItem
     * renderItem

***********************************************************************/
void fired::InventoryWindowItem::renderItem(sf::Text *count) {
	if (item->base == NULL) return;

	sf::Sprite *sprite = item->base->sprite->spr;

	sprite->setOrigin(item->base->sprite->size / 2.0f);
	sprite->setPosition(rectCenter(rect));
	sprite->setRotation(0.0f);
	app->draw(*sprite);

	if (item->count > 1) {
		char objCount[16];
		snprintf(objCount, sizeof(objCount), "%u", item->count);

		count->setString(sf::String(objCount));
		count->setPosition(sf::Vector2f(rect.left + rect.width  - count->getGlobalBounds().width  - 7,
		                                rect.top  + rect.height - count->getGlobalBounds().height - 7));
		app->draw(*count);
	}
}
