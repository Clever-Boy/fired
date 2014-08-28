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
	offset = sf::Vector2f(MENU_X_WINDOW_OFFSET, MENU_Y_OFFSET + MENU_Y_DIFF);
	size   = sf::Vector2f(settings->window.width - MENU_X_OFFSET, settings->window.height - MENU_X_OFFSET) - offset;

	win = new fired::Window(size);
	win->setOffset(offset);
}
