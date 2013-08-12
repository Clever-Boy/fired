#ifndef __MAINMENU
#define __MAINMENU


#define MENU_BG_SPEED 100.0


namespace fired {
	class MainMenu;
}


#include <SFML/Graphics.hpp>
#include "control.hpp"
#include "menuitem.hpp"
#include "prototypes.hpp"


namespace fired {
	enum MenuAnimationType {
		atUp,
		atDown,
		atNone
	};


	class MainMenu : public GameScreen {
	private:
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


	public:
		 MainMenu(fired::Mouse *_mouse);
		~MainMenu();

		void update();
		void render();
		void click(sf::Vector2i pos);
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
