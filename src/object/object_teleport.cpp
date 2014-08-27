/***********************************************************************
     * File       : object_teleport.cpp
     * Created    : Aug 27, 2014
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#include "game.hpp"



/***********************************************************************
     * BaseMapObjectTeleport
     * constructor

***********************************************************************/
fired::BaseMapObjectTeleport::BaseMapObjectTeleport(unsigned int id, sf::Vector2f _pos, fired::TeleportType _type) {
	type    = moTeleport;
	ttype   = _type;
	pos     = _pos;
	decorId = id;
}



/***********************************************************************
     * MapObjectTeleport
     * constructor

***********************************************************************/
fired::MapObjectTeleport::MapObjectTeleport(unsigned int _decorId, sf::Vector2f pos, fired::TeleportType _type) {
	type    = moTeleport;
	ttype   = _type;
	decorId = _decorId;
	decor   = new fired::Decor(container->decors[decorId], pos);
}
