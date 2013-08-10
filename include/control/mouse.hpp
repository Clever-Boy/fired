#ifndef __MOUSE
#define __MOUSE


#include <SFML/Graphics.hpp>
#include "prototypes.hpp"


namespace fired {
	class Mouse {
	private:
		fired::Game      *game;
		fired::Settings  *settings;
		sf::RenderWindow *app;

		sf::Vector2f pos;
		sf::Texture *mouseTex;
		sf::Sprite  *mouseCur;


	public:
		void init(fired::Game *_game);
		~Mouse();

		void update();
		void render();
	};
}

#endif
