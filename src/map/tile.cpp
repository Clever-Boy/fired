#include "game.hpp"

//======================================================================


void fired::Tile::init(int _tileset, bool _isWall, int x, int y) {
	tilesetIdx = _tileset;
	isWall     = _isWall;
	pos        = sf::Vector2f(x * TILE_SIZE, y * TILE_SIZE);

	if (isWall) color = sf::Color::White;
	else        color = sf::Color(180, 180, 180, 255);
}

//======================================================================


void fired::Tile::deinit() {
	return;
}

//======================================================================


void fired::Tile::render(sf::RenderWindow *app) {
	if (!tileset) return;

	sprite->setPosition(pos);
	sprite->setColor(color);
	app->draw(*sprite);
}

//======================================================================


void fired::Tile::setTileset(fired::Tileset *_tileset) {
	tileset = _tileset;
	if (tileset) sprite = tileset->getTile(tile);
}

//======================================================================


void fired::Tile::setTile(int _tile) {
	tile = _tile * 4 + random() % 4;
}
