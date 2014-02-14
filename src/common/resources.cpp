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
	sounds.explosion = new sf::SoundBuffer();
	sounds.explosion->loadFromFile("data/snd/misc/explosion.wav");



	win.trashTex = new sf::Texture();
	win.emptyTex = new sf::Texture();
	win.hoverTex = new sf::Texture();
	win.normalTex = new sf::Texture();

	win.trashTex->loadFromFile("data/img/gui/inventory/trash.png");
	win.emptyTex->loadFromFile("data/img/gui/inventory/empty.png");
	win.hoverTex->loadFromFile("data/img/gui/inventory/hover.png");
	win.normalTex->loadFromFile("data/img/gui/inventory/normal.png");

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



	sprites.coinTex      = new sf::Texture();
	sprites.smokeTex     = new sf::Texture();
	sprites.snowflakeTex = new sf::Texture();

	sprites.coinTex->loadFromFile("data/img/world/icons/misc/coin.png");
	sprites.smokeTex->loadFromFile("data/img/world/sprites/smoke.png");
	sprites.snowflakeTex->loadFromFile("data/img/world/sprites/snowflake.png");

	sprites.coin      = new sf::Sprite();
	sprites.smoke     = new sf::Sprite();
	sprites.snowflake = new sf::Sprite();

	sprites.coin->setTexture(*sprites.coinTex);
	sprites.smoke->setTexture(*sprites.smokeTex);
	sprites.snowflake->setTexture(*sprites.snowflakeTex);

	sprites.coin->setOrigin(sf::Vector2f(sprites.coinTex->getSize()) / 2.0f);
	sprites.smoke->setOrigin(sf::Vector2f(sprites.smokeTex->getSize()) / 2.0f);
	sprites.snowflake->setOrigin(sf::Vector2f(sprites.snowflakeTex->getSize()) / 2.0f);
}



/***********************************************************************
     * Resources
     * destructor

***********************************************************************/
fired::Resources::~Resources() {
	delete sounds.explosion;



	delete win.trashSpr;
	delete win.emptySpr;
	delete win.hoverSpr;
	delete win.normalSpr;

	delete win.trashTex;
	delete win.emptyTex;
	delete win.hoverTex;
	delete win.normalTex;



	delete sprites.coin;
	delete sprites.smoke;
	delete sprites.snowflake;

	delete sprites.coinTex;
	delete sprites.smokeTex;
	delete sprites.snowflakeTex;
}
