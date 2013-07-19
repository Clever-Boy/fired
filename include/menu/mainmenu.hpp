#ifndef __MAINMENU
#define __MAINMENU

#define MENU_BG_SPEED 100.0

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

		float xOffset;

	public:
		void init(fired::Game *_game);
		void update(float frameClock);
		void render();
	};
}
#endif
