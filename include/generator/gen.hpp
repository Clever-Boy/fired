/***********************************************************************
     * File       : gen.hpp
     * Created    : Jul 31, 2013
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#ifndef __GEN
#define __GEN


namespace fired {
	struct MapGenerator {
		fired::MapTile **tiles;
		sf::Vector2f     startPos;
		int sizeX;
		int sizeY;

		std::vector<fired::MapDecor*> decors;
		std::vector<fired::BaseMapObject*> objects;


		 MapGenerator();
		~MapGenerator();

		#include "gen_misc.hpp"
		#include "gen_biome_city.hpp"
	};
}

#endif
