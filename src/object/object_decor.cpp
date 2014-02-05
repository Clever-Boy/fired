/***********************************************************************
     * File       : object_decor.cpp
     * Created    : Sep 03, 2013
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#include "game.hpp"



/***********************************************************************
     * BaseDecor
     * constructor

***********************************************************************/
fired::BaseDecor::BaseDecor(const char *_name, sf::Vector2f _size, fired::GameSprite *_sprite) {
	strncpy(name, _name, sizeof(name));

	size = _size;
	sprite = _sprite;
}



/***********************************************************************
     * Decor
     * constructor

***********************************************************************/
fired::Decor::Decor(fired::BaseDecor *_base, sf::Vector2f _pos) {
	pos    = _pos;
	base   = _base;
	sprite = _base->sprite->spr;
	rect   = sf::FloatRect(pos, base->size);
	color  = sf::Color::White;
}



/***********************************************************************
     * Decor
     * render

***********************************************************************/
void fired::Decor::render() {
	sprite->setPosition(pos);
	sprite->setColor(color);
	app->draw(*sprite);
}
