#include "game.hpp"


void fired::Map::init(fired::Game *_game) {
	game = _game;

	tileset.init("data/img/tilesets/grass.tga");
}



void fired::Map::deinit() {
	tileset.deinit();
}



void fired::Map::render() {
	return;
}
