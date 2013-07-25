#include "game.hpp"


void fired::Tile::init(fired::Tileset *_tileset, int x, int y) {
	tileset = _tileset;
	pos     = sf::Vector2f(x * TILE_SIZE, y * TILE_SIZE);
	tile    = random() % 4;
}



void fired::Tile::deinit() {
	return;
}



void fired::Tile::render(fired::Game *game) {
	if (!tileset) return;

	sf::Sprite *sprite = tileset->getTile(tile);
	sprite->setPosition(pos);
	game->getApp()->draw(*sprite);
}
