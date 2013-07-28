#ifndef __WORLD
#define __WORLD


#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include "map.hpp"
#include "char.hpp"
#include "prototypes.hpp"


namespace fired {
	class World {
	private:
		fired::Game      *game;
		fired::Settings  *settings;
		sf::RenderWindow *app;
		b2World          *physWorld; 

		fired::Map    map;
		fired::Camera cam;
		fired::Player player;


	public:
		void init(fired::Game *_game);
		void deinit();
		void update();
		void processEvent(sf::Event event);
		void checkControls();
	};
}

#endif
