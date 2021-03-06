/***********************************************************************
     * File       : object_base.cpp
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
fired::BaseMapObject::BaseMapObject(unsigned int id, sf::Vector2f _pos, fired::MapObjectType _type) {
	type    = _type;
	pos     = _pos;
	decorId = id;
}



/***********************************************************************
     * MapObject
     * constructor

***********************************************************************/
fired::MapObject::MapObject(unsigned int _decorId, sf::Vector2f pos) {
	type    = moNone;
	decorId = _decorId;
	decor   = new fired::Decor(container->decors[decorId], pos);
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
void fired::MapObject::render(fired::Map *map) {
	update(map);
	if (decor) decor->render();
}
