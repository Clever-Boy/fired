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
     * MapObjectCollector
     * constructor

***********************************************************************/
fired::MapObjectLightSource::MapObjectLightSource(fired::Decor *_decor) {
	type = moLightSource;
	decor = _decor;
}
