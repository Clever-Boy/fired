/***********************************************************************
     * File       : object_lightsource.hpp
     * Created    : Jan 31, 2014
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#ifndef __OBJECT_LIGHTSOURCE
#define __OBJECT_LIGHTSOURCE

#include "object_base.hpp"


namespace fired {
	struct BaseLightSource {
		char              name[64];
		char              intensity;
		sf::Vector2i      offset;
		sf::Color         color;
		fired::BaseDecor *decor;
	};



	struct BaseMapObjectLightSource : BaseMapObject {
		char name[64];


		BaseMapObjectLightSource() {};
		BaseMapObjectLightSource(const char *_name, sf::Vector2f _pos);
	};



	struct MapObjectLightSource : MapObject {
		char name[64];
		sf::Vector2i offset;
		sf::Vector2i index;
		sf::Color    color;
		char         intensity;


		MapObjectLightSource(fired::BaseLightSource *_base, sf::Vector2f _pos);

		void update(fired::Map *map);
	};
}

#endif
