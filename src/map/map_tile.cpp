/***********************************************************************
     * File       : map_tile.cpp
     * Created    : Jul 24, 2013
     * Copyright  : (C) 2014 Achpile
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
	index      = sf::Vector2i(x, y);
	intensity  = 0;

	if (!tileset)    absorb = 4;
	else if (isWall) absorb = 15;
	else             absorb = 4;

	if (isWall) color = sf::Color::White;
	else        color = sf::Color(140, 140, 140, 255);
}



/***********************************************************************
     * Tile
     * render

***********************************************************************/
void fired::Tile::render() {
	if (!tileset) return;

	if (spriteBack) {
		spriteBack->setPosition(pos);
		spriteBack->setColor(sf::Color(140, 140, 140, 255));
		app->draw(*spriteBack);
	}

	sprite->setPosition(pos);
	sprite->setColor(color);
	app->draw(*sprite);
}



/***********************************************************************
     * Tile
     * setTileset

***********************************************************************/
void fired::Tile::setTileset() {
	if (tileset == 0) sprite = NULL;
	else sprite = container->tilesets[tileset - 1]->sprites[tile];

	if ((tileset == 0) || (tile == tileBack) || (!isWall) || (container->tilesets[tileset - 1]->flat)) spriteBack = NULL;
	else spriteBack = container->tilesets[tileset - 1]->sprites[tileBack];
}



/***********************************************************************
     * Tile
     * setTile

***********************************************************************/
void fired::Tile::setTile(int _tile) {
	tile = _tile;
}



/***********************************************************************
     * Tile
     * setTileBack

***********************************************************************/
void fired::Tile::setTileBack(int _tile) {
	tileBack = _tile;
}
