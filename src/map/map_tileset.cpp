/***********************************************************************
     * File       : map_tileset.cpp
     * Created    : Jul 24, 2013
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#include "game.hpp"



/***********************************************************************
     * Tileset
     * constructor

***********************************************************************/
fired::Tileset::Tileset(int _ID, fired::GameSprite *baseSprite, bool _flat, char *_name) {
	ID   = _ID;
	flat = _flat;
	strcpy(name, _name);

	sf::Image          maskImg;
	sf::RenderTexture *text    = new sf::RenderTexture;
	sf::Sprite        *sprt    = new sf::Sprite;
	sf::Sprite        *mask    = new sf::Sprite;
	sf::Texture       *maskTex;

	if (flat) maskTex = resources->masks.flat;
	else      maskTex = resources->masks.bumpy;

	baseSprite->tex->setRepeated(true);
	mask->setTexture(*maskTex);

	sprt->setTexture(*baseSprite->tex);
	sprt->setTextureRect(sf::IntRect(0, 0, 64, 64));

	text->create(64, 64);
	text->draw(*sprt);
	text->draw(*mask);
	text->display();

	maskImg = text->getTexture().copyToImage();
	maskImg.createMaskFromColor(sf::Color(255, 0, 255));

	tex = new sf::Texture();
	tex->loadFromImage(maskImg);

	delete text;
	delete sprt;
	delete mask;

	for (int j = 0; j < 4; j++)
		for (int i = 0; i < 4; i++) {
			sprites.push_back(new sf::Sprite());
			sprites.back()->setTexture(*tex);
			sprites.back()->setTextureRect(sf::IntRect(TILE_SIZE * i, TILE_SIZE * j, TILE_SIZE, TILE_SIZE));
		}

	baseSprite->tex->setRepeated(false);
}



/***********************************************************************
     * Tileset
     * destructor

***********************************************************************/
fired::Tileset::~Tileset() {
	deleteList(sprites);
	delete tex;
}
