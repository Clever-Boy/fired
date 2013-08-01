#ifndef __THEMAP
#define __THEMAP


#include <SFML/Graphics.hpp>
#include "tile.hpp"
#include "tileset.hpp"
#include "prototypes.hpp"
#include "phys.hpp"


namespace fired {
	class Map {
	private:
		fired::Game      *game;
		fired::Settings  *settings;
		sf::RenderWindow *app;
		fired::Camera    *cam;

		std::vector<fired::Tileset*> tilesets;
		fired::Tile  **tiles;

		sf::Texture        *bgTex;
		sf::RectangleShape *bgSprite;

		sf::Vector2i        visibleTiles;
		sf::Vector2i        mapSize;
		sf::Vector2f        startPos;

		int sizeX;
		int sizeY;


	public:
		void init(fired::Game *_game, fired::Camera *_cam);
		void deinit();
		void update();
		void render();

		void load(const char* filename);
		void save(const char* filename);

		void findTiles(int x1, int y1, int x2, int y2);
		void findTile(int i, int j);

		void checkPhys(fired::Phys *phys);
		bool isSolid(int i, int j);
		sf::Vector2i getSize() { return mapSize; };
		sf::Vector2f getStartPos() { return startPos; };
	};
}

#endif
