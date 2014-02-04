/***********************************************************************
     * File       : temporary_light.cpp
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
}



/***********************************************************************
     * Tile
     * update

***********************************************************************/
bool fired::TemporaryLightSource::update() {
	if ((lifetime -= frameClock) == 0) return false;

	intensity = (char)(baseIntensity * lifetime / maxLife);
	if (map->tiles[index.x][index.y].intensity < intensity)
		map->tiles[index.x][index.y].intensity = intensity;

	return true;
}
