#include "game.hpp"

//======================================================================


fired::Creature::Creature(fired::Game *_game, fired::Camera *_cam, sf::Vector2f _startpos, fired::World *world, fired::BaseCreature *base) {
	game     = _game;
	settings = game->getSettings();
	app      = game->getApp();

	character = new fired::Character(_game, _cam, _startpos, world, base);
	ai        = world->getAI(base->ai, this);
}

//======================================================================


fired::Creature::~Creature() {
	delete character;
	delete ai;
}

//======================================================================


void fired::Creature::update() {
	ai->update();
	character->update();
}
