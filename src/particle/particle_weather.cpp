/***********************************************************************
     * File       : particle_weather.cpp
     * Created    : Feb 12, 2014
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#include "game.hpp"



/***********************************************************************
     * ParticleSystemWeather
     * constructor

***********************************************************************/
fired::ParticleSystemWeather::ParticleSystemWeather(fired::World *world) : fired::ParticleSystemSpray(sf::Vector2f(0,0), sf::Vector2f(0,0), world, sf::Color::White, 0, 0, 0, 1, true, &world->cam->offset) {
	cam = world->cam;
}
