/***********************************************************************
     * File       : map_tileset.cpp
     * Created    : Jul 24, 2013
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#include "game.hpp"



/***********************************************************************
     * Class
     * constructor

***********************************************************************/
fired::Tileset::Tileset(int _ID, fired::GameSprite *baseSprite) {
	ID = _ID;

	sf::RenderTexture *text    = new sf::RenderTexture;
	sf::Sprite        *sprt    = new sf::Sprite;
	sf::Sprite        *mask    = new sf::Sprite;
	sf::Texture       *maskTex = new sf::Texture();
	maskTex->loadFromFile("data/img/world/tileset/mask.tga");

	baseSprite->tex->setRepeated(true);
	mask->setTexture(*maskTex);

	sprt->setTexture(*baseSprite->tex);
	sprt->setTextureRect(sf::IntRect(0, 0, 64, 64));

	text->create(64, 64);
	text->draw(*sprt);
	text->draw(*mask);
	text->display();

	tex = new sf::Texture(text->getTexture());

	delete text;
	delete sprt;
	delete mask;
	delete maskTex;

	for (int j = 0; j < 4; j++)
		for (int i = 0; i < 4; i++) {
			sprites.push_back(new sf::Sprite());
			sprites.back()->setTexture(*tex);
			sprites.back()->setTextureRect(sf::IntRect(TILE_SIZE * i, TILE_SIZE * j, TILE_SIZE, TILE_SIZE));
		}

	baseSprite->tex->setRepeated(false);
}



/***********************************************************************
     * Class
     * destructor

***********************************************************************/
fired::Tileset::~Tileset() {
	deleteList(sprites);
	delete tex;
}
