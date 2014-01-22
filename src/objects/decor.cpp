/***********************************************************************
     * File       : decor.cpp
     * Created    : Sep 03, 2013
     * Copyright  : (C) 2013 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#include "game.hpp"



/***********************************************************************
     * MapDecor
     * constructor

***********************************************************************/
fired::MapDecor::MapDecor(const char *_name, sf::Vector2f _pos) {
	strncpy(name, _name, sizeof(name));
	pos = _pos;
}



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
fired::Decor::Decor(fired::BaseDecor *base, sf::Vector2f _pos) {
	pos    = _pos;
	rect   = sf::FloatRect(pos, base->size);
	sprite = base->sprite->spr;
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
