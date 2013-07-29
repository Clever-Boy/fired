#ifndef __MODEL
#define __MODEL


#include <SFML/Graphics.hpp>
#include "prototypes.hpp"


namespace fired {
	class Model {
	private:
		fired::Game      *game;
		fired::Settings  *settings;
		fired::Character *owner;
		sf::RenderWindow *app;

		sf::Sprite   *sprite;
		sf::Texture  *texture;


	public:
		void init(fired::Game *_game, fired::Character *_owner);
		void deinit();
		void update();
		void render();
	};
}

#endif
