/***********************************************************************
     * File       : control_mouse.cpp
     * Created    : Jul 26, 2013
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#include "game.hpp"



/***********************************************************************
     * Mouse
     * constructor

***********************************************************************/
fired::Mouse::Mouse() {
	mouseTex = new sf::Texture();
	mouseCur = new sf::Sprite();

	mouseTex->loadFromFile("data/img/gui/mainmenu/mouse.png");
	mouseCur->setTexture(*mouseTex);
	mouseTex->setSmooth(true);
}



/***********************************************************************
     * Mouse
     * destructor

***********************************************************************/
fired::Mouse::~Mouse() {
	delete mouseTex;
	delete mouseCur;
}



/***********************************************************************
     * Mouse
     * update

***********************************************************************/
void fired::Mouse::update() {
	pos = sf::Vector2f(sf::Mouse::getPosition(*app));
	render();
}



/***********************************************************************
     * Mouse
     * render

***********************************************************************/
void fired::Mouse::render() {
	mouseCur->setPosition(pos);
	app->draw(*mouseCur);
}
