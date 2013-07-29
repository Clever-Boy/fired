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
		sf::Sprite   *spriteShoe;
		sf::Sprite   *spriteFist;

		sf::Texture  *textureHair;
		sf::Texture  *textureHead;
		sf::Texture  *textureBody;
		sf::Texture  *textureLegs;
		sf::Texture  *textureArms;
		sf::Texture  *textureShoe;
		sf::Texture  *textureFist;


	public:
		void init(fired::Game *_game, fired::Character *_owner);
		void deinit();
		void update();
		void render();
	};
}

#endif
