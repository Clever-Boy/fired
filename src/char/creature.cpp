#include "game.hpp"

//======================================================================


void fired::Creature::init(fired::Game *_game, sf::Vector2f _startpos, fired::World *world) {
	game     = _game;
	settings = game->getSettings();
	app      = game->getApp();

	character.init(_game, _startpos, world);
}

//======================================================================


void fired::Creature::deinit() {
	character.deinit();
}

//======================================================================


void fired::Creature::update() {
	character.update();
}
