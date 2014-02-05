/***********************************************************************
     * File       : menu_base.hpp
     * Created    : Jul 18, 2013
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#ifndef __MENU_BASE
#define __MENU_BASE


namespace fired {
	struct MainMenu;
}


#include "menu_item.hpp"


namespace fired {
	enum MenuAnimationType {
		atUp,
		atDown,
		atNone
	};


	struct MainMenu : GameScreen {
		std::vector<fired::MenuItem *> menuItems;
		fired::Mouse     *mouse;

		sf::Texture *bgTexture;
		sf::Texture *menuItemTexture;
		sf::Texture *logoTexture;

		sf::RectangleShape *bgSprite;
		sf::Sprite         *menuItemSprite;
		sf::Sprite         *logoSprite;

		sf::Text           *menuCaption;
		sf::SoundBuffer    *clickBuffer;
		sf::Sound          *clickSound;

		fired::MenuItem *currentMenu;
		fired::MenuItem *nextMenu;
		fired::MenuAnimationType animation;

		float xOffset;


		 MainMenu(fired::Mouse *_mouse);
		~MainMenu();

		void update();
		void render();
		void click(sf::Vector2f pos);
		void processEvent(sf::Event event);

		void fillMenu();
		void fillMenuBack();
		void menuItemAdd(const char *_caption, fired::MenuItem *_parent, fired::MenuItemType itemType, fired::Handler handlerFunc);
		void switchMenu(fired::MenuItem *menuItem);
		void setNextMenu(fired::MenuItem *menuItem);
		void initAnimation(fired::MenuAnimationType animType);
		void processAnimation();
		void updateSettings();
	};
}

#endif
