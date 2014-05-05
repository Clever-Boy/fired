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

	limit = 1;
	value = 0;

	caption = new sf::Text;
	caption->setFont(*game->font);
	caption->setCharacterSize(14);
	caption->setColor(sf::Color::Black);
	caption->setPosition(pos.x + 50.0f, pos.y);
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
	resources->progress.full->setTextureRect(sf::IntRect(0, 0, PROGRESSBAR_WIDTH * ((float)value / (float)limit), PROGRESSBAR_HEIGHT));

	resources->progress.border->setPosition(pos);
	resources->progress.empty->setPosition(pos);
	resources->progress.full->setPosition(pos);

	app->draw(*resources->progress.empty);
	app->draw(*resources->progress.full);
	app->draw(*resources->progress.border);
	app->draw(*caption);
}



/***********************************************************************
     * ProgressBar
     * setCaption

***********************************************************************/
void fired::ProgressBar::setCaption(const char *_caption, const char *_subject) {
	char newCaption[128];
	snprintf(newCaption, sizeof(newCaption), "%s %s", _caption, _subject);

	caption->setString(sf::String(newCaption));
}
