#ifndef __MAINMENU
#define __MAINMENU

#include <SFML/Graphics.hpp>
#include "menuitem.hpp"

namespace fired {
	class MainMenu {
	private:
		fired::MenuItem MenuItem;

		sf::Image BackgroundImage;
		sf::Image MenuItemImage;
		sf::Image LogoImage

		sf::Sprite BackgroundSprite;
		sf::Sprite MenuItemSprite;
		sf::Sprite LogoSprite;

	public:
		void Init();
		void Update();
		void Render();
	};
}
#endif
