#include "game.hpp"

//======================================================================


void fired::Tile::init(int _tileset, int x, int y) {
	tilesetIdx = _tileset;
	pos        = sf::Vector2f(x * TILE_SIZE, y * TILE_SIZE);
	tile       = random() % 4;
}

//======================================================================


void fired::Tile::deinit() {
	return;
}

//======================================================================


void fired::Tile::render(sf::RenderWindow *app) {
	if (!tileset) return;

	sprite->setPosition(pos);
	app->draw(*sprite);
}

//======================================================================


void fired::Tile::setTileset(fired::Tileset *_tileset) {
	tileset = _tileset;
	if (tileset) sprite = tileset->getTile(tile);
}
