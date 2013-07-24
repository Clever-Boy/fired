#ifndef __KEYBOARD
#define __KEYBOARD


#include <SFML/Graphics.hpp>
#include "prototypes.hpp"


namespace fired {
	class Keyboard {
	private:
		fired::Game *game;


	public:
		void processEvent(sf::Event event);
		void init(fired::Game *_game);
	};
}

#endif
