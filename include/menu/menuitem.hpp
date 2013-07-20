#ifndef __MENUITEM
#define __MENUITEM

#define MENU_FONT_FILE "data/fonts/advanced_pixel-7.ttf"
#define MENU_FONT_SIZE 32
#define MENU_Y_OFFSET  1.5


#include <SFML/Graphics.hpp>
#include "prototypes.hpp"

namespace fired {
	class MenuItem {
		friend class fired::MainMenu;
	private:
		fired::Game  *game;
		sf::Sprite   *sprite;
		sf::String   caption;
		sf::Text     text;
		sf::Font     *font;

		sf::Vector2f pos;

		float xOffset;

		fired::MenuItem *parent;
		std::vector<fired::MenuItem*> subMenu;
	public:
		void init(fired::Game *_game, sf::Sprite *_sprite, sf::Font *_font, const char *_caption, fired::MenuItem *_parent);
		void update(float frameClock);
		void render();

		void addSubMenu(fired::MenuItem *subMenuItem);
		void addToParent();
	};
}
#endif
