#include "game.hpp"


//======================================================================


fired::InventoryItem::InventoryItem(fired::ItemType _type, unsigned int _count, const char *_name, fired::World *world) {
	init(_type, _count, _name, world);
}

//======================================================================


fired::InventoryItem::InventoryItem(fired::MapItem *base, fired::World *world) {
	init(base->type, base->count, base->name, world);
}

//======================================================================


void fired::InventoryItem::init(fired::ItemType _type, unsigned int _count, const char *_name, fired::World *world) {
	strncpy(name   , _name, sizeof(name));
	strncpy(caption, _name, sizeof(caption));

	count = _count;
	type  = _type;

	switch (type) {
		case itMoney:
			sprite = world->getSprite("coin");
			color  = sf::Color::White;
			break;

		case itWeapon:
			sprite = world->getBodypart(world->getWeapon(name)->model, bptWeapon)->chunk;
			color  = sf::Color::White;
			break;

		case itArmorHelm:
			sprite = world->getBodypart(world->getArmor(name, acHelm)->model, bptHair)->chunk;
			color  = world->getArmor(name, acHelm)->color;
			break;

		case itArmorBody:
			sprite = world->getBodypart(world->getArmor(name, acBody)->model, bptBody)->chunk;
			color  = world->getArmor(name, acBody)->color;
			break;

		case itArmorLegs:
			sprite = world->getBodypart(world->getArmor(name, acLegs)->model, bptLegsF)->chunk;
			color  = world->getArmor(name, acLegs)->color;
			break;

		case itArmorFist:
			sprite = world->getBodypart(world->getArmor(name, acFist)->model, bptFistF)->chunk;
			color  = world->getArmor(name, acFist)->color;
			break;

		case itArmorShoe:
			sprite = world->getBodypart(world->getArmor(name, acShoe)->model, bptShoeF)->chunk;
			color  = world->getArmor(name, acShoe)->color;
			break;

		case itArmorArms:
			sprite = world->getBodypart(world->getArmor(name, acArms)->model, bptArms)->chunk;
			color  = world->getArmor(name, acArms)->color;
			break;

		case itAny:
			break;
	}
}

//======================================================================


void fired::InventoryItem::render(sf::Vector2f pos) {
	if (sprite == NULL) return;

	sprite->setPosition(pos);
	sprite->setColor(color);
	sprite->setRotation(0.0f);
	app->draw(*sprite);
}
