#ifndef __CHARACTER
#define __CHARACTER

#include <SFML/Graphics.hpp>
#include "prototypes.hpp"


namespace fired {
	class Character {
	private:
		fired::Game      *game;
		fired::Settings  *settings;
		sf::RenderWindow *app;

		sf::Sprite   *sprite;
		sf::Texture  *texture;
		sf::Vector2f  pos;
		sf::Vector2f  size;


	public:
		void init(fired::Game *_game);
		void deinit();
		void update(float frameClock);
		void render();
	};
}

#endif
