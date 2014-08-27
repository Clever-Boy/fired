/***********************************************************************
     * File       : menu_window.hpp
     * Created    : Aug 26, 2014
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#ifndef __MENU_WINDOW
#define __MENU_WINDOW


#include "input.hpp"


namespace fired {
	struct MenuItemWindow {
		sf::Vector2f size;
		sf::Vector2f offset;


		virtual ~MenuItemWindow()        {};

		virtual void update()            {};
		virtual void render()            {};
		virtual void click(sf::Vector2f) {};
	};
}

#endif
