#include "game.hpp"

//======================================================================


void fired::Container::init(fired::Game *_game, fired::World *_world) {
	game     = _game;
	settings = game->getSettings();
	app      = game->getApp();
	world    = _world;
}

//======================================================================


void fired::Container::deinit() {
	return;
}
