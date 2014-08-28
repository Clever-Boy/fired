/***********************************************************************
     * File       : menu_window.cpp
     * Created    : Aug 28, 2014
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#include "game.hpp"



/***********************************************************************
     * MenuItemWindow
     * constructor

***********************************************************************/
fired::MenuItemWindow::MenuItemWindow() {
	sf::Vector2f from(MENU_X_WINDOW_OFFSET, MENU_Y_OFFSET + MENU_Y_DIFF);
	sf::Vector2f to(settings->window.width - MENU_X_OFFSET, settings->window.height - MENU_X_OFFSET);

	win = new fired::Window(to - from);
	win->setOffset(from);
}
