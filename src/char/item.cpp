#include "game.hpp"


//======================================================================


fired::InventoryItem::InventoryItem(fired::ItemType _type, unsigned int _count, const char *_name, fired::World *world) {
	strncpy(name   , _name, sizeof(name));
	strncpy(caption, _name, sizeof(caption));

	count = _count;
	type  = _type;

	switch (type) {
		case itMoney:
			sprite = world->getSprite("coin");
			break;

		case itWeapon:
			sprite = world->getBodypart(world->getWeapon(name)->model, bptWeapon)->chunk;
			break;
	}
}

//======================================================================


void fired::InventoryItem::render(sf::Vector2f pos) {
	if (sprite == NULL) return;

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
