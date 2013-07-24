#ifndef __WORLD
#define __WORLD


#include <SFML/Graphics.hpp>
#include "map.hpp"
#include "prototypes.hpp"


namespace fired {
	class World {
	private:
		fired::Game *game;
		fired::Map map;


	public:
		void init(fired::Game *_game);
		void deinit();
		void update(float frameClock);
		void render();
		void processEvent(sf::Event event);
	};
}

#endif
