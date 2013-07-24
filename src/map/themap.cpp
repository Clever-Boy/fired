#include "game.hpp"


void fired::Map::init(fired::Game *_game) {
	game = _game;

	tileset.init("data/img/tilesets/grass.tga");

	for (int i = 0; i < 100; i++) for (int j = 0; j < 100; j++) {
		tiles[i][j].init(NULL, i, j);
	}

	// Test map generation
	for (int i = 4; i <= 20; i++) {
		tiles[i][20].init(&tileset, i, 20);
		tiles[i][4].init(&tileset, i, 4);
		tiles[20][i].init(&tileset, 20, i);
		tiles[4][i].init(&tileset, 4, i);
	}
}



void fired::Map::deinit() {
	tileset.deinit();
}



void fired::Map::render() {
	for (int i = 0; i < 100; i++)
		for (int j = 0; j < 100; j++)
			tiles[i][j].render(game);
}
