#include "game.hpp"

//======================================================================


fired::Creature::Creature(fired::Game *_game, fired::Camera *_cam, sf::Vector2f _startpos, fired::World *world, fired::BaseCreature *base) {
	game     = _game;
	settings = game->getSettings();
	app      = game->getApp();

	character = new fired::Character(_game, _cam, _startpos, world, base);
	left = false;
}

//======================================================================


fired::Creature::~Creature() {
	delete character;
}

//======================================================================


void fired::Creature::update() {
	if (left) {
		if (character->phys.pos.x < 140*16.0) left = false;
		character->moveLeft();
		character->setAiming(3.14);
	} else {
		if (character->phys.pos.x > 158*16.0) left = true;
		character->moveRight();
		character->setAiming(0);
	}

	character->update();
}
