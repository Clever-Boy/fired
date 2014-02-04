/***********************************************************************
     * File       : themap.hpp
     * Created    : Jul 24, 2013
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#ifndef __THEMAP
#define __THEMAP


namespace fired {
	struct Map;
}


#include "defines.hpp"
#include "tile.hpp"
#include "objects.hpp"
#include "phys.hpp"
#include "biome.hpp"
#include "world.hpp"


namespace fired {
	struct Map {
		fired::Camera    *cam;
		fired::World     *world;

		fired::Tile   **tiles;
		fired::Biome   *biome;

		sf::Vertex sky[4];

		std::vector<fired::Decor*>     decors;
		std::vector<fired::MapObject*> objects;

		sf::Vector2i        visibleTiles;
		sf::Vector2i        mapSize;
		sf::Vector2f        startPos;

		sf::Vertex          lightMask[4];

		fired::Tile **lightTiles[LIGHT_MAX_LIGHTLEVEL];
		int           lightCounts[LIGHT_MAX_LIGHTLEVEL];

		int sizeX;
		int sizeY;


		 Map(fired::Camera *_cam, fired::World *_world);
		~Map();

		void update();
		void render();
		void spawn();

		bool isSolid(int i, int j);
		bool isPlatform(int i, int j, fired::Phys *phys);
		void findTile(int i, int j);
		void findTiles(int x1, int y1, int x2, int y2) {for (int i = x1; i < x2; i++) for (int j = y1; j < y2; j++) findTile(i, j); };

		void checkCollision(fired::Phys *phys, fired::Character *character, int tile_x, int tile_y);
		void checkPhys(fired::Phys *phys, fired::Character *character, float tunnelTime);
		bool checkShot(fired::Shot *shot);

		fired::MapObject *checkInteraction(fired::Character *owner);

		#include "lighting.hpp"
	};
}

#endif
