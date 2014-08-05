/***********************************************************************
     * File       : map_spawn.hpp
     * Created    : Jul 24, 2013
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#ifndef __MAP_SPAWN
#define __MAP_SPAWN


#include "map_tileset.hpp"


namespace fired {
	enum MapSpawnType {
		mstCommon  = 1,
		mstBoss    = 2,
		mstCritter = 4
	};


	struct MapSpawn {
		int         type;
		sf::IntRect spawn;


		MapSpawn() {};
		MapSpawn(sf::IntRect _spawn, int _type);
	};
}

#endif
