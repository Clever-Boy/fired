#include "game.hpp"


void fired::World::init(fired::Game *_game) {
	game = _game;
}



void fired::World::deinit() {
	return;
}



void fired::World::update(float frameClock) {
	render();
}



void fired::World::render() {
	return;
}



void fired::World::processEvent(sf::Event event) {
	return;
}
