/***********************************************************************
     * File       : weather_storm.cpp
     * Created    : Feb 14, 2014
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#include "game.hpp"



/***********************************************************************
     * WeatherStorm
     * constructor

***********************************************************************/
fired::WeatherStorm::WeatherStorm(fired::World *_world, float _frequency, float _wind) : Weather(_world, _frequency, _wind) {
	sprite = new sf::RectangleShape(sf::Vector2f(3, 16));
	sprite->setOrigin(sf::Vector2f(1.5, 0));
	sprite->setRotation(wind);
	sprite->setFillColor(sf::Color(150,150,164,195));

	float angle = (90 + wind) * 3.14 / 180.0;
	speed = sf::Vector2f(650.0 * cos(angle), 650.0 * sin(angle));
	accel = sf::Vector2f(350.0 * cos(angle), 350.0 * sin(angle));

	lightning     = NULL;
	lightningTime = 0.0f;
}



/***********************************************************************
     * WeatherStorm
     * destructor

***********************************************************************/
fired::WeatherStorm::~WeatherStorm() {
	if (lightning) delete lightning;
}



/***********************************************************************
     * WeatherStorm
     * update

***********************************************************************/
void fired::WeatherStorm::update() {
	Weather::update();

	if (lightning) {
		if (lightning->update()) {
			delete lightning;
			lightning = NULL;
		} else
			lightning->draw();
	}

	lightningTime -= frameClock;
	if (lightningTime < 0) genLightning();
}



/***********************************************************************
     * WeatherStorm
     * genLightning

***********************************************************************/
void fired::WeatherStorm::genLightning() {
	if (lightning) delete lightning;

	sf::Vector2f start, end;

	start    = cam->offset;
	start.x += (float)(random() % settings->window.width);

	end    = start;
	end.y += (float)settings->window.height;

	lightning     = new fired::Lightning(start, end);
	lightningTime = LIGHTNING_MIN_TIME + (LIGHTNING_MAX_TIME - LIGHTNING_MIN_TIME) * ((float)(random() % 100) / 100.0);
}
