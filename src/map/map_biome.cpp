/***********************************************************************
     * File       : map_biome.cpp
     * Created    : Jan 22, 2014
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#include "game.hpp"



/***********************************************************************
     * Biome
     * constructor

***********************************************************************/
fired::Biome::Biome(const char *bgFile) {
	float scaleFactor;

	bgTex    = new sf::Texture();
	bgSprite = new sf::RectangleShape();

	bgTex->loadFromFile(bgFile);
	bgSprite->setTexture(bgTex);
	bgTex->setRepeated(true);
	bgTex->setSmooth(true);
	bgSprite->setSize(sf::Vector2f(settings->window.width, settings->window.height));

	scaleFactor = (float)settings->window.height / (float)bgTex->getSize().y;
	bgSprite->setScale(scaleFactor, scaleFactor);
}



/***********************************************************************
     * Biome
     * destructor

***********************************************************************/
fired::Biome::~Biome() {
	delete bgSprite;
	delete bgTex;
}
