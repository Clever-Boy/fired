/***********************************************************************
     * File       : log_base.cpp
     * Created    : Aug 19, 2014
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#include "game.hpp"



/***********************************************************************
     * Log
     * constructor

***********************************************************************/
fired::Log::Log(sf::FloatRect rect) {
	messages.clear();

	win = new fired::Window(sf::Vector2f(rect.width, rect.height));
	win->offset = sf::Vector2f(rect.left, rect.top);
}



/***********************************************************************
     * Log
     * destructor

***********************************************************************/
fired::Log::~Log() {
	deleteList(messages);
	delete win;
}



/***********************************************************************
     * Log
     * update

***********************************************************************/
void fired::Log::update() {
	updateList(messages);
	while (messages.size() > LOG_SIZE) {
		delete messages[0];
		messages.erase(messages.begin());
	}

	render();
}



/***********************************************************************
     * Log
     * render

***********************************************************************/
void fired::Log::render() {
	win->render();
}
