#ifndef __THEMAP
#define __THEMAP


#include <SFML/Graphics.hpp>
#include "tile.hpp"
#include "tileset.hpp"
#include "prototypes.hpp"
#include "phys.hpp"
#include "theworld.hpp"


namespace fired {
	class Map {
	private:
		fired::Camera    *cam;
		fired::World     *world;

		fired::Tileset *tileset;
		fired::Tile   **tiles;

		std::vector<fired::Decor*> decors;


		sf::Texture        *bgTex;
		sf::RectangleShape *bgSprite;


		sf::Vector2i        visibleTiles;
		sf::Vector2i        mapSize;
		sf::Vector2f        startPos;

		int sizeX;
		int sizeY;


	public:
		 Map(fired::Camera *_cam, fired::World *_world);
		~Map();

		void update();
		void render();

		void load(const char* filename);
		void save(const char* filename);

		bool isSolid(int i, int j);
		void findTile(int i, int j);
		void findTiles(int x1, int y1, int x2, int y2) {for (int i = x1; i < x2; i++) for (int j = y1; j < y2; j++) findTile(i, j); };

		void checkCollision(fired::Phys *phys, fired::Character *character, int tile_x, int tile_y);
		void checkPhys(fired::Phys *phys, fired::Character *character);
		bool checkShot(fired::Shot *shot);

		sf::Vector2i getSize()     { return mapSize; };
		sf::Vector2f getStartPos() { return startPos; };
	};
}

#endif
