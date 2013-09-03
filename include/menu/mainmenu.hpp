#ifndef __MAINMENU
#define __MAINMENU


namespace fired {
	struct MainMenu;
}


#include "menuitem.hpp"


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
