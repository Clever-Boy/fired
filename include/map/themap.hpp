#ifndef __THEMAP
#define __THEMAP


#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
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
		b2World          *physWorld;
		fired::Camera    *cam;

		fired::Tileset tileset;
		fired::Tile    tiles[200][200];

		sf::Texture        *bgTex;
		sf::RectangleShape *bgSprite;
		sf::Vector2i        visibleTiles;

	public:
		void init(fired::Game *_game, fired::Camera *_cam, b2World *_physWorld);
		void deinit();
		void update();
		void render();

		void initPhys();
	};
}

#endif
