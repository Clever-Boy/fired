#ifndef __MENUITEM
#define __MENUITEM


#include "control.hpp"


namespace fired {
	enum MenuItemType {
		itBack,
		itSubmenu,
		itButton
	};


	class MenuItem {
		friend class fired::MainMenu;


	private:
		fired::MainMenu *mainMenu;
		sf::Sprite      *sprite;
		sf::String      *caption;
		sf::Text        *text;
		sf::Font        *font;

		fired::Handler handlerFunc;
		sf::Vector2f   pos;

		float xOffset;
		float yOffset;
		float timeOffset;

		fired::MenuItem              *parent;
		fired::MenuItemType           itemType;
		std::vector<fired::MenuItem*> subMenu;


	public:
		 MenuItem(fired::MainMenu *_mainMenu, sf::Sprite *_sprite, const char *_caption, fired::MenuItem *_parent, fired::MenuItemType _itemType, fired::Handler _handlerFunc);
		~MenuItem();

		void update();
		void render();
		void click();

		void addSubMenu(fired::MenuItem *subMenuItem);
		void addToParent();
	};
}

#endif
