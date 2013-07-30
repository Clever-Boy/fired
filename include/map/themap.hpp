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

		fired::Tileset tileset;
		fired::Tile  **tiles;

		sf::Texture        *bgTex;
		sf::RectangleShape *bgSprite;
		sf::Vector2i        visibleTiles;

		int sizeX;
		int sizeY;


	public:
		void init(fired::Game *_game, fired::Camera *_cam);
		void deinit();
		void update();
		void render();

		void checkPhys(fired::Phys *phys);
	};
}

#endif
