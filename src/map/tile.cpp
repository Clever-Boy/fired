#include "game.hpp"

//======================================================================


void fired::Tile::init(int _tileset, bool _isWall, int x, int y) {
	tileset = _tileset;
	isWall  = _isWall;
	pos     = sf::Vector2f(x * TILE_SIZE, y * TILE_SIZE);

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
	if (tileset == 0) sprite = NULL;
	else sprite = _tileset->getTile((tileset - 1) * 16 + tile);
}

//======================================================================


void fired::Tile::setTile(int _tile) {
	tile = _tile;
}
