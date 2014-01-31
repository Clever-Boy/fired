/***********************************************************************
     * File       : lightsource.hpp
     * Created    : Jan 31, 2014
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#ifndef __LIGHTSOURCE
#define __LIGHTSOURCE

#include "map_objects.hpp"


namespace fired {
	struct BaseLightSource {
		char              name[64];
		char              intensity;
		sf::Vector2i      offset;
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
		char         intensity;


		MapObjectLightSource(fired::BaseLightSource *_base, sf::Vector2f _pos);

		void update();
	};
}

#endif
