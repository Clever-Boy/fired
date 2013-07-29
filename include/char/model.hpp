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

		sf::Sprite   *spriteHair;
		sf::Sprite   *spriteHead;
		sf::Sprite   *spriteBody;
		sf::Sprite   *spriteLegs;
		sf::Sprite   *spriteArms;

		sf::Texture  *textureHair;
		sf::Texture  *textureHead;
		sf::Texture  *textureBody;
		sf::Texture  *textureLegs;
		sf::Texture  *textureArms;


	public:
		void init(fired::Game *_game, fired::Character *_owner);
		void deinit();
		void update();
		void render();
	};
}

#endif
