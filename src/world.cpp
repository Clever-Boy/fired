#include "game.hpp"


void fired::World::init(fired::Game *_game) {
	game     = _game;
	settings = game->getSettings();
	app      = game->getApp();

	map.init(game, &cam);
	cam.init(game);
	player.init(game);

	cam.setTrackObj(&player.phys);
}



void fired::World::deinit() {
	map.deinit();
	player.deinit();
}



void fired::World::update() {
	checkControls();
	map.checkPhys(&player.phys);

	cam.update();
	map.update();
	player.update();
}



void fired::World::checkControls() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))     player.moveLeft();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))     player.moveRight();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) player.jump();
}



void fired::World::processEvent(sf::Event event) {
	return;
}
