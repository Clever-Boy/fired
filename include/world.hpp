#ifndef __WORLD
#define __WORLD


#include <SFML/Graphics.hpp>
#include "map.hpp"
#include "prototypes.hpp"


#define PHYS_GRAVITY  5.0
#define PHYS_MAX_FALL 250.0


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
		void processEvent(sf::Event event);

		void checkControls();
	};
}

#endif
