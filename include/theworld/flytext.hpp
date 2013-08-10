#ifndef __FLYTEXT
#define __FLYTEXT


#include <SFML/Graphics.hpp>
#include "prototypes.hpp"

#define FLYTEXT_LIFETIME 0.5
#define FLYTEXT_OFFSET   20.0


namespace fired {
	class FlyText {
	private:
		fired::Game      *game;
		fired::Settings  *settings;
		sf::RenderWindow *app;

		sf::Vector2f pos;
		sf::Color    color;
		float        life;

		sf::String  *flyStr;
		sf::Text    *flyTxt;

	public:
		void init(fired::Game *_game, sf::Vector2f _pos, sf::Color _color, int size, const char *text);
		~FlyText();

		bool update();
		void render();
	};
}

#endif
