/***********************************************************************
     * File       : lightsource.cpp
     * Created    : Jan 31, 2014
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#include "game.hpp"



/***********************************************************************
     * BaseMapObjectLightSource
     * constructor

***********************************************************************/
fired::BaseMapObjectLightSource::BaseMapObjectLightSource(const char *_name, sf::Vector2f _pos) {
	type = moLightSource;
	pos  = _pos;

	strncpy(name, _name, sizeof(name));
}



/***********************************************************************
     * MapObjectLightSource
     * constructor

***********************************************************************/
fired::MapObjectLightSource::MapObjectLightSource(fired::BaseLightSource *_base, sf::Vector2f pos) {
	type      = moLightSource;
	intensity = _base->intensity;
	color     = _base->color;
	offset    = _base->offset;
	decor     = new fired::Decor(_base->decor, pos);

	strcpy(name, _base->name);
}



/***********************************************************************
     * MapObjectLightSource
     * update

***********************************************************************/
void fired::MapObjectLightSource::update(fired::Map *map) {
	int x = (int)(decor->pos.x / TILE_SIZE + 0.5f) + offset.x;
	int y = (int)(decor->pos.y / TILE_SIZE + 0.5f) + offset.y;
	map->tiles[x][y].intensity = intensity;
}
