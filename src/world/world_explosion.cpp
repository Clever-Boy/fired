/***********************************************************************
     * File       : world_explosion.cpp
     * Created    : Aug 26, 2013
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#include "game.hpp"



/***********************************************************************
     * BaseExplosion
     * constructor

***********************************************************************/
fired::BaseExplosion::BaseExplosion(const char *filename) {
	tex = new sf::Texture();
	tex->loadFromFile(filename);
	tex->setSmooth(true);

	sf::Vector2f origin(tex->getSize().y / 2, tex->getSize().y / 2);

	int step   = tex->getSize().y;
	int frames = (int)(tex->getSize().x / tex->getSize().y);
	radius     = tex->getSize().y / 2.0f;

	for (int i = 0; i < frames; i++) {
		spr.push_back(new sf::Sprite());
		spr[i]->setTexture(*tex);
		spr[i]->setOrigin(origin);
		spr[i]->setTextureRect(sf::IntRect(step * i, 0, step, tex->getSize().y));
	}
}



/***********************************************************************
     * BaseExplosion
     * destructor

***********************************************************************/
fired::BaseExplosion::~BaseExplosion() {
	deleteList(spr);
	delete tex;
}
