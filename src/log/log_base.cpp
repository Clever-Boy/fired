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
	win->setOffset(sf::Vector2f(rect.left, rect.top));
	win->text->setCharacterSize(LOG_MESSAGE_HEIGHT);
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

	for (unsigned int i = 0; i < messages.size(); i++)
		win->renderText(5, i * LOG_MESSAGE_HEIGHT, messages[i]->text, taLeft);
}
