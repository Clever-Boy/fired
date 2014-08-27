/***********************************************************************
     * File       : object_teleport.hpp
     * Created    : Aug 27, 2014
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#ifndef __OBJECT_TELEPORT
#define __OBJECT_TELEPORT

#include "object_base.hpp"


namespace fired {
	enum TeleportType {
		ttHome,
		ttCity
	};



	struct BaseMapObjectTeleport : BaseMapObject {
		fired::TeleportType ttype;


		BaseMapObjectTeleport() {};
		BaseMapObjectTeleport(unsigned int id, sf::Vector2f _pos, fired::TeleportType _type);
	};



	struct MapObjectTeleport : MapObject {
		fired::TeleportType ttype;


		MapObjectTeleport(unsigned int _decorId, sf::Vector2f pos, fired::TeleportType _type);
	};
}

#endif
