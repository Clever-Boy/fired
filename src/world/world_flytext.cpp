/***********************************************************************
     * File       : world_flytext.cpp
     * Created    : Aug 26, 2013
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#include "game.hpp"



/***********************************************************************
     * FlyText
     * constructor

***********************************************************************/
fired::FlyText::FlyText(sf::Vector2f _pos, sf::Color _color, int size, const char *text) {
	pos      = _pos;
	color    = _color;
	life     = 0;

	flyStr = new sf::String(text);
	flyTxt = new sf::Text;
	flyTxt->setFont(*resources->fonts.game);
	flyTxt->setString(*flyStr);
	flyTxt->setCharacterSize(size);
	flyTxt->setStyle(sf::Text::Bold);
}



/***********************************************************************
     * FlyText
     * destructor

***********************************************************************/
fired::FlyText::~FlyText() {
	delete flyStr;
	delete flyTxt;
}



/***********************************************************************
     * FlyText
     * update

***********************************************************************/
bool fired::FlyText::update() {
	life += frameClock;

	if (life > FLYTEXT_LIFETIME / 2)
		color.a = 255 * (0.5 - life / FLYTEXT_LIFETIME);
	else
		color.a = 255;

	if (life > FLYTEXT_LIFETIME) return false;

	render();
	return true;
}



/***********************************************************************
     * FlyText
     * render

***********************************************************************/
void fired::FlyText::render() {
	flyTxt->setPosition(pos - sf::Vector2f(0, life * FLYTEXT_OFFSET / FLYTEXT_LIFETIME));
	flyTxt->setColor(color);
	app->draw(*flyTxt);
}
