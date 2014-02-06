/***********************************************************************
     * File       : object_lightsource.cpp
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
fired::BaseMapObjectLightSource::BaseMapObjectLightSource(unsigned int _id, sf::Vector2f _pos) {
	type = moLightSource;
	pos  = _pos;
	id   = _id;
}



/***********************************************************************
     * MapObjectLightSource
     * constructor

***********************************************************************/
fired::MapObjectLightSource::MapObjectLightSource(unsigned int _id, sf::Vector2f pos) {
	id        = _id;
	type      = moLightSource;

	fired::BaseLightSource *base = container->lights[id];
	intensity = base->intensity;
	color     = base->color;
	offset    = base->offset;
	decor     = new fired::Decor(base->decor, pos);

	index.x = (int)(decor->pos.x / TILE_SIZE + 0.5f) + offset.x;
	index.y = (int)(decor->pos.y / TILE_SIZE + 0.5f) + offset.y;
}



/***********************************************************************
     * MapObjectLightSource
     * update

***********************************************************************/
void fired::MapObjectLightSource::update(fired::Map *map) {
	map->addIntensity(index, intensity, color);
}
