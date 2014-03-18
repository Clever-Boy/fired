/***********************************************************************
     * File       : gen_base.hpp
     * Created    : Jul 31, 2013
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#ifndef __GEN_BASE
#define __GEN_BASE

#include "gen_tileset.hpp"


namespace fired {
	struct MapGenerator {
		fired::Biome    *biome;
		fired::MapTile **tiles;
		sf::Vector2f     startPos;
		int sizeX;
		int sizeY;
		int brush;

		std::vector<fired::BaseMapObject*> objects;
		std::vector<fired::GenTileset*>    palette;


		 MapGenerator(fired::Biome *_biome);
		~MapGenerator();

		#include "gen_misc.hpp"
		#include "gen_biome_city.hpp"
	};
}

#endif
