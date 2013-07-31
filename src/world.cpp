#include "game.hpp"

//======================================================================


void fired::World::init(fired::Game *_game) {
	game     = _game;
	settings = game->getSettings();
	app      = game->getApp();

	game->setMusic("data/snd/themes/world.ogg");

	map.init(game, &cam);
	cam.init(game, map.getSize());
	player.init(game, &cam, map.getStartPos());

	cam.setTrackObj(player.getPhys());
}

//======================================================================


void fired::World::deinit() {
	map.deinit();
	player.deinit();
}

//======================================================================


void fired::World::update() {
	checkControls();
	map.checkPhys(player.getPhys());

	cam.update();
	map.update();
	player.update();
}

//======================================================================


void fired::World::checkControls() {
	player.checkControls();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) game->stop();
}

//======================================================================


void fired::World::processEvent(sf::Event event) {
	return;
}
