/***********************************************************************
     * File       : screen_progressbar.cpp
     * Created    : Jul 22, 2013
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#include "game.hpp"



/***********************************************************************
     * ProgressBar
     * constructor

***********************************************************************/
fired::ProgressBar::ProgressBar(sf::Vector2f _pos) {
	pos = _pos;
}



/***********************************************************************
     * ProgressBar
     * destructor

***********************************************************************/
fired::ProgressBar::~ProgressBar() {
	return;
}



/***********************************************************************
     * ProgressBar
     * render

***********************************************************************/
void fired::ProgressBar::render() {
	resources->progress.border->setPosition(pos);
	resources->progress.empty->setPosition(pos);
	resources->progress.full->setPosition(pos);

	app->draw(*resources->progress.empty);
	app->draw(*resources->progress.full);
	app->draw(*resources->progress.border);
}
