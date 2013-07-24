#ifndef __MENUITEM
#define __MENUITEM


#define MENU_X_OFFSET 50
#define MENU_Y_OFFSET 150
#define MENU_Y_DIFF   75


#include <SFML/Graphics.hpp>
#include "prototypes.hpp"


namespace fired {
	enum MenuItemType {
		itBack,
		itSubmenu,
		itWindow,
		itButton
	};


	class MenuItem {
		friend class fired::MainMenu;


	private:
		fired::Game     *game;
		fired::MainMenu *mainMenu;
		sf::Sprite      *sprite;
		sf::String      *caption;
		sf::Text        *text;
		sf::Font        *font;

		fired::Handler handlerFunc;
		sf::Vector2f pos;

		float xOffset;
		float yOffset;
		float timeOffset;

		fired::MenuItem *parent;
		fired::MenuItemType itemType;
		std::vector<fired::MenuItem*> subMenu;


	public:
		void init(fired::Game *_game, fired::MainMenu *_mainMenu, sf::Sprite *_sprite, sf::Font *_font, const char *_caption, fired::MenuItem *_parent, fired::MenuItemType _itemType, fired::Handler _handlerFunc);
		void deinit();
		void update(float frameClock);
		void render();
		void click();

		void addSubMenu(fired::MenuItem *subMenuItem);
		void addToParent();
	};
}

#endif
