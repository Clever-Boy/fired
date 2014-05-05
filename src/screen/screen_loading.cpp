/***********************************************************************
     * File       : screen_loading.cpp
     * Created    : May 05, 2014
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#include "game.hpp"



/***********************************************************************
     * LoadingScr
     * constructor

***********************************************************************/
fired::LoadingScr::LoadingScr() {
	timeOffset = 0;

	texture = new sf::Texture();
	texture->loadFromFile("data/img/gui/loadingscr/splash.jpg");

	sprite = new sf::Sprite();
	sprite->setTexture(*texture);
	sprite->move((settings->window.width - texture->getSize().x) / 2, (settings->window.height - texture->getSize().y) / 2);

	mainBar = new fired::ProgressBar(sf::Vector2f((settings->window.width - PROGRESSBAR_WIDTH) / 2, (settings->window.height - PROGRESSBAR_HEIGHT) / 2 + 100));
	secBar  = new fired::ProgressBar(sf::Vector2f((settings->window.width - PROGRESSBAR_WIDTH) / 2, (settings->window.height - PROGRESSBAR_HEIGHT) / 2 + 150));
}



/***********************************************************************
     * LoadingScr
     * destructor

***********************************************************************/
fired::LoadingScr::~LoadingScr() {
	delete texture;
	delete sprite;

	delete mainBar;
	delete secBar;
}



/***********************************************************************
     * LoadingScr
     * update

***********************************************************************/
void fired::LoadingScr::update() {
	render();

	container = new fired::Container();
	game->setGameState(gsStartScr);
}



/***********************************************************************
     * LoadingScr
     * render

***********************************************************************/
void fired::LoadingScr::render() {
	app->clear();

	app->draw(*sprite);
	mainBar->render();
	secBar->render();

	app->display();
}
