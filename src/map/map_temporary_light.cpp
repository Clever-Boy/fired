/***********************************************************************
     * File       : map_temporary_light.cpp
     * Created    : Jul 24, 2013
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#include "game.hpp"



/***********************************************************************
     * TemporaryLightSource
     * constructor

***********************************************************************/
fired::TemporaryLightSource::TemporaryLightSource(char _intensity, float _lifetime, sf::Vector2f _pos, sf::Color _color, fired::Map *_map) {
	intensity = _intensity;
	lifetime  = _lifetime;
	pos       = _pos;
	color     = _color;
	map       = _map;

	maxLife = lifetime;
	baseIntensity = intensity;
	index = sf::Vector2i((int)(pos.x / TILE_SIZE), (int)(pos.y / TILE_SIZE));

	if (index.x < 0)           index.x = 0;
	if (index.y < 0)           index.y = 0;
	if (index.x >= map->sizeX) index.x = map->sizeX - 1;
	if (index.y >= map->sizeY) index.y = map->sizeY - 1;
}



/***********************************************************************
     * Tile
     * update

***********************************************************************/
bool fired::TemporaryLightSource::update() {
	if ((lifetime -= frameClock) < 0.0f) return false;

	intensity = (char)(baseIntensity * lifetime / maxLife);
	map->addIntensity(index, intensity, color);

	return true;
}
