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



void fired::World::update(float frameClock) {
	render();

	map.update();
	player.update(frameClock);
}



void fired::World::render() {
	return;
}



void fired::World::processEvent(sf::Event event) {
	return;
}
