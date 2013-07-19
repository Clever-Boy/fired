#ifndef __MAINMENU
#define __MAINMENU

#include <SFML/Graphics.hpp>
#include "menuitem.hpp"
#include "prototypes.hpp"

namespace fired {
	class MainMenu {
	private:
		fired::MenuItem MenuItem;
		fired::Game *Game;

		sf::Image BackgroundImage;
		sf::Image MenuItemImage;
		sf::Image LogoImage;

		sf::Sprite BackgroundSprite;
		sf::Sprite MenuItemSprite;
		sf::Sprite LogoSprite;

	public:
		void Init(fired::Game *game);
		void Update();
		void Render();
	};
}
#endif
