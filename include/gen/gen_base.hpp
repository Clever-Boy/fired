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
		fired::Biome            *biome;
		fired::MapTile         **tiles;
		fired::WorldProperties   worldProps;
		sf::IntRect              startRect;
		int sizeX;
		int sizeY;
		int brush;

		std::vector<fired::BaseMapObject*> objects;
		std::vector<fired::GenTileset*>    palette;
		std::vector<fired::MapSpawn*>      spawns;


		 MapGenerator(const char *location);
		 MapGenerator(fired::Biome *_biome, fired::WorldProperties _worldProps);
		~MapGenerator();


		#include "gen_misc.hpp"

		#include "gen_biome_building.hpp"
		#include "gen_biome_mine.hpp"
		#include "gen_biome_snow.hpp"
		#include "gen_biome_sewers.hpp"
		#include "gen_biome_castle.hpp"
		#include "gen_biome_cave.hpp"
		#include "gen_biome_city.hpp"
		#include "gen_biome_mountains.hpp"
		#include "gen_biome_graveyard.hpp"
		#include "gen_biome_forest.hpp"
	};
}

#endif
