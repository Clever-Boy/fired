#include "game.hpp"


//======================================================================


fired::InventoryItem::InventoryItem() {
	base  = NULL;
	count = 0;
}

//======================================================================


fired::InventoryItem::InventoryItem(fired::BaseItem *_base, unsigned int _count) {
	base  = _base;
	count = _count;
}

//======================================================================


void fired::InventoryItem::render(sf::Vector2f pos) {
	sf::Sprite *sprite = base->sprite->spr;
	if (sprite == NULL) return;

	sprite->setOrigin(base->sprite->size / 2.0f);
	sprite->setPosition(pos);
	sprite->setRotation(0.0f);
	app->draw(*sprite);
}
