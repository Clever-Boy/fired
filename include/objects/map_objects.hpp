/***********************************************************************
     * File       : map_objects.hpp
     * Created    : Sep 03, 2013
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#ifndef __MAP_OBJECTS
#define __MAP_OBJECTS

#include "decor.hpp"


namespace fired {
	enum MapObjectType {
		moNone,
		moCollector,
		moLightSource
	};



	struct BaseMapObject {
		char                 decorName[16];
		sf::Vector2f         pos;
		fired::MapObjectType type;


		BaseMapObject() {};
		BaseMapObject(const char *_name, sf::Vector2f _pos, fired::MapObjectType _type);
	};



	struct MapObject {
		fired::Decor        *decor;
		fired::MapObjectType type;


		 MapObject() {};
		 MapObject(fired::Decor *_decor);
		~MapObject();

		void render();
	};
}

#endif
