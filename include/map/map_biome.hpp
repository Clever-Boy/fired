/***********************************************************************
     * File       : map_biome.hpp
     * Created    : Jan 22, 2014
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#ifndef __MAP_BIOME
#define __MAP_BIOME


namespace fired {
	struct Biome {
		char name[64];
		char weather[64];
		char background[128];
		char intensity;

		sf::Color lightness;
		std::vector<fired::BaseCreature*> creatures;
		std::vector<fired::BaseCreature*> critters;
		std::vector<fired::BaseCreature*> bosses;


		fired::Weather *getWeather(fired::World *world);
	};
}

#endif
