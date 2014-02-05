/***********************************************************************
     * File       : object_base.hpp
     * Created    : Sep 03, 2013
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#ifndef __OBJECT_BASE
#define __OBJECT_BASE

#include "object_decor.hpp"


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
		virtual ~MapObject();

		virtual void update(fired::Map*) {};
		void render(fired::Map *map);
	};
}

#endif
