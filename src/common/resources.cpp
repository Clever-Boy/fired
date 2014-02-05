/***********************************************************************
     * File       : resources.cpp
     * Created    : Aug 02, 2013
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#include "game.hpp"



/***********************************************************************
     * Resources
     * constructor

***********************************************************************/
fired::Resources::Resources() {
	sounds.explosion_buf = new sf::SoundBuffer();
	sounds.explosion_buf->loadFromFile("data/snd/misc/explosion.wav");

	sounds.explosion = new sf::Sound();
	sounds.explosion->setBuffer(*sounds.explosion_buf);
	sounds.explosion->setVolume(settings->volume.sound);



	win.trashTex = new sf::Texture();
	win.emptyTex = new sf::Texture();
	win.hoverTex = new sf::Texture();
	win.normalTex = new sf::Texture();

	win.trashTex->loadFromFile("data/img/gui/inventory/trash.tga");
	win.emptyTex->loadFromFile("data/img/gui/inventory/empty.tga");
	win.hoverTex->loadFromFile("data/img/gui/inventory/hover.tga");
	win.normalTex->loadFromFile("data/img/gui/inventory/normal.tga");

	win.trashSpr = new sf::Sprite();
	win.emptySpr = new sf::Sprite();
	win.hoverSpr = new sf::Sprite();
	win.normalSpr = new sf::Sprite();

	win.trashSpr->setTexture(*win.trashTex);
	win.emptySpr->setTexture(*win.emptyTex);
	win.hoverSpr->setTexture(*win.hoverTex);
	win.normalSpr->setTexture(*win.normalTex);

	win.trashSpr->setOrigin(sf::Vector2f(win.trashTex->getSize())   / 2.0f);
	win.emptySpr->setOrigin(sf::Vector2f(win.emptyTex->getSize())   / 2.0f);
	win.hoverSpr->setOrigin(sf::Vector2f(win.hoverTex->getSize())   / 2.0f);
	win.normalSpr->setOrigin(sf::Vector2f(win.normalTex->getSize()) / 2.0f);



	sprites.coinTex = new sf::Texture();
	sprites.coinTex->loadFromFile("data/img/world/icons/misc/coin.tga");

	sprites.coin = new sf::Sprite();
	sprites.coin->setTexture(*sprites.coinTex);
	sprites.coin->setOrigin(sf::Vector2f(sprites.coinTex->getSize()) / 2.0f);
}



/***********************************************************************
     * Resources
     * destructor

***********************************************************************/
fired::Resources::~Resources() {
	delete sounds.explosion;
	delete sounds.explosion_buf;



	delete win.trashSpr;
	delete win.emptySpr;
	delete win.hoverSpr;
	delete win.normalSpr;

	delete win.trashTex;
	delete win.emptyTex;
	delete win.hoverTex;
	delete win.normalTex;



	delete sprites.coin;

	delete sprites.coinTex;
}
