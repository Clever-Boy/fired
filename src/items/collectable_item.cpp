#include "game.hpp"


//======================================================================


fired::CollectableItem::CollectableItem(fired::InventoryItem *_item, sf::Vector2f pos, sf::Vector2f velocity, fired::World *_world) {
	item  = _item;
	world = _world;

	phys.size         = sf::Vector2f(8, 8);
	phys.pos          = pos;
	phys.velocity     = velocity;
	phys.acceleration = sf::Vector2f(0, PHYS_GRAVITY / 4);

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
