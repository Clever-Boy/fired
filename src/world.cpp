#include "game.hpp"


void fired::World::init(fired::Game *_game) {
	game = _game;
	map.init(game);
	player.init(game);
}



void fired::World::deinit() {
	map.deinit();
	player.deinit();
}



void fired::World::update() {
	checkControls();

	map.update();
	map.checkPhys(&player.phys);

	player.update();
}



void fired::World::checkControls() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) player.moveLeft();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) player.moveRight();
}



void fired::World::processEvent(sf::Event event) {
	return;
}
