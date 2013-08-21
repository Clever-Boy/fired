#include "game.hpp"


//======================================================================


void fired::InventoryItem::render(sf::Vector2f pos) {
	sprite->setPosition(pos);
	app->draw(*sprite);
}

//======================================================================


fired::CollectableItem::CollectableItem() {
	return;
}

//======================================================================


void fired::CollectableItem::render() {
	item->sprite->setPosition(phys.pos);
	app->draw(*item->sprite);
}
