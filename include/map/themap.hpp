#ifndef __THEMAP
#define __THEMAP


#include <SFML/Graphics.hpp>
#include "tile.hpp"
#include "tileset.hpp"
#include "prototypes.hpp"
#include "phys.hpp"
#include "world.hpp"
#include "theworld.hpp"


namespace fired {
	class Map {
	private:
		fired::Game      *game;
		fired::Settings  *settings;
		sf::RenderWindow *app;
		fired::Camera    *cam;
		fired::World     *world;

		fired::Tileset tileset;
		fired::Tile  **tiles;

		sf::Texture        *bgTex;
		sf::RectangleShape *bgSprite;

		sf::Vector2i        visibleTiles;
		sf::Vector2i        mapSize;
		sf::Vector2f        startPos;

		int sizeX;
		int sizeY;


	public:
		void init(fired::Game *_game, fired::Camera *_cam, fired::World *_world);
		void deinit();
		void update();
		void render();

		void load(const char* filename);
		void save(const char* filename);

		void findTiles(int x1, int y1, int x2, int y2);
		void findTile(int i, int j);

		void checkCollision(fired::Character *character, int tile_x, int tile_y);

		void checkPhys(fired::Character *character);
		bool checkShot(fired::Shot *shot);

		bool isSolid(int i, int j);
		sf::Vector2i getSize() { return mapSize; };
		sf::Vector2f getStartPos() { return startPos; };
	};
}

#endif
