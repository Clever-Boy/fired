/***********************************************************************
     * File       : map_base.hpp
     * Created    : Jul 24, 2013
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#ifndef __MAP_BASE
#define __MAP_BASE


namespace fired {
	struct Map;
}


#include "defines.hpp"
#include "map_tile.hpp"
#include "map_spawn.hpp"
#include "object.hpp"
#include "map_temporary_light.hpp"
#include "weather.hpp"
#include "misc/misc_phys.hpp"
#include "map_biome.hpp"
#include "world.hpp"


namespace fired {
	struct Map {
		fired::Camera    *cam;
		fired::World     *world;

		fired::Tile            **tiles;
		fired::Biome            *biome;
		fired::Weather          *weather;
		fired::WorldProperties   worldProps;

		std::vector<fired::MapObject*>            objects;
		std::vector<fired::TemporaryLightSource*> lights;
		std::vector<fired::MapSpawn*>             spawns;

		sf::Texture        *bgTex;
		sf::RectangleShape *bgSprite;
		float               bgScale;

		sf::Vector2i        visibleTiles;
		sf::IntRect         startRect;

		sf::Vertex          lightMask[4];

		fired::Tile **lightTiles[LIGHT_MAX_LIGHTLEVEL];
		int           lightCounts[LIGHT_MAX_LIGHTLEVEL];

		int sizeX;
		int sizeY;


		 Map(fired::Camera *_cam, fired::World *_world);
		~Map();

		void update();
		void render();
		void setWeather();
		void spawn(sf::Vector2f position, fired::MapSpawnType type);

		void findTile(int i, int j);
		void findTiles(int x1, int y1, int x2, int y2) {for (int i = x1; i < x2; i++) for (int j = y1; j < y2; j++) findTile(i, j); };

		fired::MapObject *checkInteraction(fired::Character *owner);
		sf::Vector2f getPlayerSpawn();
		sf::IntRect  getRectToSpawn(fired::BaseCreature *creature, sf::IntRect spawnRect);

		#include "map_lighting.hpp"
		#include "map_physics.hpp"
	};
}

#endif
