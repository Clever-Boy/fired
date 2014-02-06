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
		unsigned int id;


		BaseMapObjectLightSource() {};
		BaseMapObjectLightSource(unsigned int _id, sf::Vector2f _pos);
	};



	struct MapObjectLightSource : MapObject {
		unsigned int id;
		sf::Vector2i offset;
		sf::Vector2i index;
		sf::Color    color;
		char         intensity;


		MapObjectLightSource(unsigned int _id, sf::Vector2f _pos);

		void update(fired::Map *map);
	};
}

#endif
