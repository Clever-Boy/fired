/***********************************************************************
     * File       : weather_rain.cpp
     * Created    : Feb 14, 2014
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#include "game.hpp"



/***********************************************************************
     * WeatherRain
     * constructor

***********************************************************************/
fired::WeatherRain::WeatherRain(fired::World *_world, float _frequency, float _wind) : Weather(_world, _frequency, _wind) {
	sprite = new sf::RectangleShape(sf::Vector2f(2, 16));
	sprite->setOrigin(sf::Vector2f(1, 0));
	sprite->setRotation(wind);
	sprite->setFillColor(sf::Color(200,200,255,195));

	float angle = (90 + wind) * 3.14 / 180.0;
	speed = sf::Vector2f(650.0 * cos(angle), 650.0 * sin(angle));
	accel = sf::Vector2f(350.0 * cos(angle), 350.0 * sin(angle));

	resources->sounds.rainSnd->play();
}



/***********************************************************************
     * WeatherRain
     * destructor

***********************************************************************/
fired::WeatherRain::~WeatherRain() {
	resources->sounds.rainSnd->stop();
}
