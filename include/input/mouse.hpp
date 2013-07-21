#ifndef __MOUSE
#define __MOUSE

#include <SFML/Graphics.hpp>
#include "prototypes.hpp"

namespace fired {
	class Mouse {
	private:
		fired::Game *game;
		sf::Vector2f pos;

		sf::Texture mouseTex;
		sf::Sprite  mouseCur;
	public:
		void init(fired::Game *_game);
		void update(float frameClock);
		void render();

		void processEvent(sf::Event event);
	};
}

#endif
