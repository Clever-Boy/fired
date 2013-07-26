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

		fired::Tileset tileset;
		fired::Tile    tiles[50][38];

		sf::Texture        *bgTex;
		sf::RectangleShape *bgSprite;

	public:
		void init(fired::Game *_game);
		void deinit();
		void update();
		void render();

		void checkPhys(fired::Phys *phys);
	};
}

#endif
