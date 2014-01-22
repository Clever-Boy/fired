/***********************************************************************
     * File       : tile.cpp
     * Created    : Jul 24, 2013
     * Copyright  : (C) 2013 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#include "game.hpp"



/***********************************************************************
     * Tile
     * set

***********************************************************************/
void fired::Tile::set(int _tileset, bool _isWall, bool _isPlatform, int x, int y) {
	tileset    = _tileset;
	isWall     = _isWall;
	isPlatform = _isPlatform;
	pos        = sf::Vector2f(x * TILE_SIZE, y * TILE_SIZE);

	if (isWall) color = sf::Color::White;
	else        color = sf::Color(140, 140, 140, 255);
}



/***********************************************************************
     * Tile
     * render

***********************************************************************/
void fired::Tile::render() {
	if (!tileset) return;

	sprite->setPosition(pos);
	sprite->setColor(color);
	app->draw(*sprite);
}



/***********************************************************************
     * Tile
     * setTileset

***********************************************************************/
void fired::Tile::setTileset(fired::Tileset *_tileset) {
	if (tileset == 0) sprite = NULL;
	else sprite = _tileset->sprites[(tileset - 1) * 16 + tile];
}



/***********************************************************************
     * Tile
     * setTile

***********************************************************************/
void fired::Tile::setTile(int _tile) {
	tile = _tile;
}
