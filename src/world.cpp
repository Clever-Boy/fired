#include "game.hpp"


void fired::World::init(fired::Game *_game) {
	game = _game;
	map.init(game);
}



void fired::World::deinit() {
	map.deinit();
}



void fired::World::update(float frameClock) {
	render();
}



void fired::World::render() {
	map.render();
}



void fired::World::processEvent(sf::Event event) {
	return;
}
