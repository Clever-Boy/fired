/***********************************************************************
     * File       : win_menu.hpp
     * Created    : May 07, 2014
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#ifndef __WIN_MENU
#define __WIN_MENU


#include "win_base.hpp"


namespace fired {
	struct MenuWindow {
		fired::Window *win;
		fired::World  *world;

		sf::Text           *text;
		sf::RectangleShape *button;


		 MenuWindow(fired::World *_world);
		~MenuWindow();

		void update(sf::Vector2f mousePos);
		void render(sf::Vector2f mousePos);
		void renderButton(float y, const char *caption, sf::Vector2f mousePos);
		void click(sf::Vector2f mousePos);
	};
}

#endif
