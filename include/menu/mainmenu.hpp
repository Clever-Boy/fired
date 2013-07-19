#ifndef __MAINMENU
#define __MAINMENU

#include <SFML/Graphics.hpp>
#include "menuitem.hpp"
#include "prototypes.hpp"

namespace fired {
	class MainMenu {
	private:
		fired::MenuItem menuItem;
		fired::Game *game;

		sf::Texture bgTexture;
		sf::Texture menuItemTexture;
		sf::Texture logoTexture;

		sf::RectangleShape bgSprite;
		sf::Sprite menuItemSprite;
		sf::Sprite logoSprite;

		sf::Font menuFont;

	public:
		void init(fired::Game *_game);
		void update(float frameClock);
		void render();
	};
}
#endif
