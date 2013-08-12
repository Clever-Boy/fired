#include "game.hpp"

//======================================================================


fired::Creature::Creature(fired::Camera *_cam, sf::Vector2f _startpos, fired::World *world, fired::BaseCreature *base) {
	character = new fired::Character(_cam, _startpos, world, base);
	ai        = world->getAI(base->ai, this);
}

//======================================================================


fired::Creature::~Creature() {
	delete character;
	delete ai;
}

//======================================================================


void fired::Creature::update() {
	character->shot();
	character->update();
}
