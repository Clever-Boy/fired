/***********************************************************************
     * File       : camera.cpp
     * Created    : Jul 26, 2013
     * Copyright  : (C) 2013 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#include "game.hpp"



/***********************************************************************
     * Camera
     * constructor

***********************************************************************/
fired::Camera::Camera() {
	viewport = sf::FloatRect(0, 0, settings->window.width, settings->window.height);
	view.reset(viewport);
}



/***********************************************************************
     * Camera
     * update

***********************************************************************/
void fired::Camera::update() {
	offset = sf::Vector2f(objToTrack->center.x - settings->window.width  / 2,
	                      objToTrack->center.y - settings->window.height / 2);

	if (offset.x < 0) offset.x = 0;
	if (offset.y < 0) offset.y = 0;

	if (offset.x > mapSize.x - settings->window.width ) offset.x = mapSize.x - settings->window.width;
	if (offset.y > mapSize.y - settings->window.height) offset.y = mapSize.y - settings->window.height;

	viewport.left = offset.x;
	viewport.top  = offset.y;

	view.setCenter(offset + sf::Vector2f(settings->window.width / 2, settings->window.height / 2));
	app->setView(view);
}



/***********************************************************************
     * Camera
     * isRectVisible

***********************************************************************/
bool fired::Camera::isRectVisible(sf::FloatRect rect) {
	return viewport.intersects(rect);
}



/***********************************************************************
     * Camera
     * isPixelVisible

***********************************************************************/
bool fired::Camera::isPixelVisible(sf::Vector2f pixel) {
	return viewport.contains(pixel);
}



/***********************************************************************
     * Camera
     * reset

***********************************************************************/
void fired::Camera::reset() {
	view.setCenter(sf::Vector2f(settings->window.width / 2, settings->window.height / 2));
	app->setView(view);
}
