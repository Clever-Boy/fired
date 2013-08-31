#ifndef __THEMAP
#define __THEMAP


#include "tile.hpp"
#include "objects.hpp"
#include "phys.hpp"
#include "world.hpp"


namespace fired {
	struct Map {
		fired::Camera    *cam;
		fired::World     *world;

		fired::Tileset *tileset;
		fired::Tile   **tiles;

		std::vector<fired::Decor*>     decors;
		std::vector<fired::MapObject*> objects;

		sf::Texture        *bgTex;
		sf::RectangleShape *bgSprite;

		sf::Vector2i        visibleTiles;
		sf::Vector2i        mapSize;
		sf::Vector2f        startPos;

		int sizeX;
		int sizeY;


		 Map(fired::Camera *_cam, fired::World *_world);
		~Map();

		void update();
		void render();

		bool isSolid(int i, int j);
		bool isPlatform(int i, int j);
		void findTile(int i, int j);
		void findTiles(int x1, int y1, int x2, int y2) {for (int i = x1; i < x2; i++) for (int j = y1; j < y2; j++) findTile(i, j); };

		void checkCollision(fired::Phys *phys, fired::Character *character, int tile_x, int tile_y);
		void checkPhys(fired::Phys *phys, fired::Character *character);
		bool checkShot(fired::Shot *shot);

		fired::MapObject *checkInteraction(fired::Character *owner);

		sf::Vector2i getSize()     { return mapSize; };
		sf::Vector2f getStartPos() { return startPos; };
	};
}

#endif
