#ifndef __KEYBOARD
#define __KEYBOARD

#include <SFML/Graphics.hpp>
#include "prototypes.hpp"

namespace fired {
	class Keyboard {
	private:
		fired::Game *Game;

	public:
		void ProcessEvent(sf::Event Event);
		void Init(fired::Game *game);
	};
}

#endif
