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

		sf::Vector2f  offsetHair;
		sf::Vector2f  offsetHead;
		sf::Vector2f  offsetBody;
		sf::Vector2f  offsetArms;
		sf::Vector2f  offsetLegsB;
		sf::Vector2f  offsetLegsF;
		sf::Vector2f  offsetFistB;
		sf::Vector2f  offsetFistF;
		sf::Vector2f  offsetShoeB;
		sf::Vector2f  offsetShoeF;


	public:
		void init(fired::Game *_game, fired::Character *_owner);
		void deinit();
		void update();
		void render();

		void initPart(sf::Sprite **spr, sf::Texture **tex, const char *imgFile);
		void drawPart(sf::Sprite *spr, sf::Vector2f offset);
	};
}

#endif
