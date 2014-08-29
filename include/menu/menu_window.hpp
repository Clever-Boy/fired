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
		fired::Window *win;
		sf::Vector2f   size;
		sf::Vector2f   offset;


		         MenuItemWindow();
		virtual ~MenuItemWindow()        { delete win; };

		virtual void update()                {};
		virtual void render()                {};
		virtual bool click(sf::Vector2f)     { return false; };
		virtual void textEntered(sf::Uint32) {};
		virtual void applyVideoSettings();
	};
}

#endif
