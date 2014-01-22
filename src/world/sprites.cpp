/***********************************************************************
     * File       : sprites.cpp
     * Created    : Aug 26, 2013
     * Copyright  : (C) 2013 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#include "game.hpp"



/***********************************************************************
     * GameSprite
     * constructor

***********************************************************************/
fired::GameSprite::GameSprite(const char *filename) {
	tex = new sf::Texture();
	tex->loadFromFile(filename);
	tex->setSmooth(true);

	spr = new sf::Sprite();
	spr->setTexture(*tex);

	size = sf::Vector2f(tex->getSize());
}



/***********************************************************************
     * GameSprite
     * destructor

***********************************************************************/
fired::GameSprite::~GameSprite() {
	delete spr;
	delete tex;
}
