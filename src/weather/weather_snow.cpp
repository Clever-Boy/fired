/***********************************************************************
     * File       : weather_snow.cpp
     * Created    : Feb 14, 2014
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#include "game.hpp"



/***********************************************************************
     * WeatherSnow
     * constructor

***********************************************************************/
fired::WeatherSnow::WeatherSnow(fired::World *_world, float _frequency, float _wind) : Weather(_world, _frequency, _wind) {
	sprite = new sf::RectangleShape(sf::Vector2f(8, 8));
	sprite->setOrigin(sf::Vector2f(4, 4));
	sprite->setTexture(resources->sprites.snowflakeTex);

	float angle = (90 + wind) * 3.14 / 180.0;
	speed = sf::Vector2f(650.0 * cos(angle), 650.0 * sin(angle) / 3.0f);
	accel = sf::Vector2f(350.0 * cos(angle), 350.0 * sin(angle) / 3.0f);
}



/***********************************************************************
     * WeatherSnow
     * genScale

***********************************************************************/
float fired::WeatherSnow::genScale() {
	return (float)(20 + random() % 80) / 100.0f;
}
