#ifndef __WORLD
#define __WORLD


#include <SFML/Graphics.hpp>
#include "map.hpp"
#include "prototypes.hpp"


namespace fired {
	class World {
	private:
		fired::Game     *game;
		fired::Map       map;
		fired::Character player;


	public:
		void init(fired::Game *_game);
		void deinit();
		void update();
		void render();
		void processEvent(sf::Event event);
	};
}

#endif
