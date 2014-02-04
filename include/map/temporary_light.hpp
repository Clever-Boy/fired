/***********************************************************************
     * File       : temporary_light.hpp
     * Created    : Feb 04, 2014
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#ifndef __TEMPORARY_LIGHT
#define __TEMPORARY_LIGHT


namespace fired {
	struct TemporaryLightSource {
		sf::Vector2f pos;
		sf::Vector2i index;
		sf::Color    color;

		char baseIntensity;
		char intensity;
		float maxLife;
		float lifetime;

		fired::Map *map;


		TemporaryLightSource(char _intensity, float _lifetime, sf::Vector2f _pos, sf::Color _color, fired::Map *_map);

		bool update();
	};
}

#endif
