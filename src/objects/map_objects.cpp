/***********************************************************************
     * File       : map_objects.cpp
     * Created    : Sep 03, 2013
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#include "game.hpp"



/***********************************************************************
     * BaseMapObject
     * constructor

***********************************************************************/
fired::BaseMapObject::BaseMapObject(const char *_name, sf::Vector2f _pos, fired::MapObjectType _type) {
	type = _type;
	pos  = _pos;

	strncpy(decorName, _name, sizeof(decorName));
}



/***********************************************************************
     * MapObject
     * constructor

***********************************************************************/
fired::MapObject::MapObject(fired::Decor *_decor) {
	type = moNone;
	decor = _decor;
}



/***********************************************************************
     * MapObject
     * destructor

***********************************************************************/
fired::MapObject::~MapObject() {
	if (decor) delete decor;
}



/***********************************************************************
     * MapObject
     * render

***********************************************************************/
void fired::MapObject::render() {
	if (decor) decor->render();
}
