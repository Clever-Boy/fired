#ifndef __MENUITEM
#define __MENUITEM

#include <SFML/Graphics.hpp>
#include "prototypes.hpp"

namespace fired {
	class MenuItem {
	private:
		fired::Game *game;
		sf::String caption;

	public:
		void init(fired::Game *_game);
		void update(float frameClock);
		void render();
	};
}
#endif
