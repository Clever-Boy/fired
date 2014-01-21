#include "game.hpp"

//======================================================================


fired::BaseCreature::BaseCreature() {
	loot.clear();
}

//======================================================================


fired::BaseCreature::~BaseCreature() {
	deleteList(loot);
}

//======================================================================


fired::Creature::Creature(fired::Camera *_cam, sf::Vector2f _startpos, fired::World *world, fired::BaseCreature *base) {
	character = new fired::Character(_cam, _startpos, world, base);
	character->generateLoot(&base->loot);
	ai = container->getAI(base->ai, this, world);
}

//======================================================================


fired::Creature::~Creature() {
	delete character;
	delete ai;
}

//======================================================================


void fired::Creature::update() {
	character->phys.jumpdown = false;

	ai->update();
	character->update();
}
