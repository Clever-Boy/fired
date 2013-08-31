#include "game.hpp"


//======================================================================


fired::MapItem::MapItem(fired::ItemType _type, unsigned int _count, const char *_name) {
	count = _count;
	type  = _type;

	strncpy(name   , _name, sizeof(name));
}

//======================================================================


fired::LootItem::LootItem(fired::ItemType _type, const char *_name, unsigned int _minCount, unsigned int _maxCount, float _probability) {
	type        = _type;
	minCount    = _minCount;
	maxCount    = _maxCount;
	probability = _probability;

	strncpy(name, _name, sizeof(name));
}

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


fired::InventoryItem::InventoryItem(fired::MapItem *base, fired::World *world) {
	strncpy(name   , base->name, sizeof(name));
	strncpy(caption, name      , sizeof(caption));

	count = base->count;
	type  = base->type;

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


fired::CollectableItem::CollectableItem(fired::InventoryItem *_item, sf::Vector2f pos, sf::Vector2f velocity, fired::World *_world) {
	item  = _item;
	world = _world;

	phys.size         = sf::Vector2f(8, 8);
	phys.pos          = pos;
	phys.velocity     = velocity;
	phys.acceleration = sf::Vector2f(0, PHYS_GRAVITY / 4);

	phys.headSize   = sf::Vector2f(0, 0);
	phys.headOffset = sf::Vector2f(0, 0);

	phys.isMoving = false;
	phys.onGround = false;
}

//======================================================================

void fired::CollectableItem::update() {
	if (phys.onGround) phys.velocity.x = 0;

	if (world->isRectVisible(phys.rect)) render();
}

//======================================================================


void fired::CollectableItem::render() {
	item->render(phys.pos);
}
