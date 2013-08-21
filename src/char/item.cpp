#include "game.hpp"


//======================================================================


fired::InventoryItem::InventoryItem(fired::ItemType _type, unsigned int _count, const char *_name) {
	strncpy(name   , _name, sizeof(name));
	strncpy(caption, _name, sizeof(caption));

	count = _count;
	type  = _type;
}

//======================================================================


void fired::InventoryItem::render(sf::Vector2f pos) {
	sprite->setPosition(pos);
	app->draw(*sprite);
}

//======================================================================


fired::CollectableItem::CollectableItem(fired::InventoryItem *_item, sf::Vector2f pos, sf::Vector2f velocity) {
	item = _item;

	phys.size         = sf::Vector2f(8, 8);
	phys.pos          = pos;
	phys.velocity     = velocity;
	phys.acceleration = sf::Vector2f(0, PHYS_GRAVITY);

	phys.headSize   = sf::Vector2f(0, 0);
	phys.headOffset = sf::Vector2f(0, 0);

	phys.isMoving = false;
	phys.onGround = false;
}

//======================================================================


void fired::CollectableItem::render() {
	item->render(phys.pos);
}
