#ifndef __MENUITEM
#define __MENUITEM

#define MENU_X_OFFSET 50
#define MENU_Y_OFFSET 150
#define MENU_Y_DIFF   75
#define MENU_WIDTH    207
#define MENU_HEIGHT   55


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
		void click();

		void addSubMenu(fired::MenuItem *subMenuItem);
		void addToParent();
	};
}
#endif
