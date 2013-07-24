#ifndef __THEWORLD
#define __THEWORLD


#include <SFML/Graphics.hpp>
#include "prototypes.hpp"


namespace fired {
	class World {
	private:
		fired::Game *game;


	public:
		void init(fired::Game *_game);
		void deinit();
		void update(float frameClock);
		void render();
		void processEvent(sf::Event event);
	};
}

#endif
