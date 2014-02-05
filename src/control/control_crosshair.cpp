/***********************************************************************
     * File       : control_crosshair.cpp
     * Created    : Jul 27, 2013
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#include "game.hpp"



/***********************************************************************
     * Crosshair
     * constructor

***********************************************************************/
fired::Crosshair::Crosshair(fired::Camera *_cam) {
	cam      = _cam;

	crosshairTex = new sf::Texture();
	crosshairCur = new sf::Sprite();

	crosshairTex->loadFromFile("data/img/gui/world/crosshair.tga");
	crosshairCur->setTexture(*crosshairTex);
	crosshairTex->setSmooth(true);
	crosshairCur->setOrigin(crosshairTex->getSize().x / 2, crosshairTex->getSize().y / 2);
}



/***********************************************************************
     * Crosshair
     * destructor

***********************************************************************/
fired::Crosshair::~Crosshair() {
	delete crosshairTex;
	delete crosshairCur;
}



/***********************************************************************
     * Crosshair
     * update

***********************************************************************/
void fired::Crosshair::update(float distance) {
	sf::Vector2f center(settings->window.width / 2, settings->window.height / 2);
	center -= (cam->offset + center - owner->center);
	pos = sf::Vector2f(sf::Mouse::getPosition(*app));

	float dist = vLen(center - pos);
	if (dist > distance) {
		pos = sf::Vector2f(center.x + (pos.x - center.x) * (distance / dist), center.y + (pos.y - center.y) * (distance / dist));
		sf::Mouse::setPosition(sf::Vector2i(pos), *app);
	}

	angle = atan2(pos.y + cam->offset.y - owner->center.y, pos.x + cam->offset.x - owner->center.x);
	render();
}



/***********************************************************************
     * Crosshair
     * render

***********************************************************************/
void fired::Crosshair::render() {
	crosshairCur->setPosition(pos + cam->offset);
	app->draw(*crosshairCur);
}
