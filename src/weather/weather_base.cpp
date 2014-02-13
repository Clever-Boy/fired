/***********************************************************************
     * File       : weather_base.cpp
     * Created    : Feb 12, 2014
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#include "game.hpp"



/***********************************************************************
     * WeatherParticle
     * process

***********************************************************************/
bool fired::WeatherParticle::process(fired::World *world) {
	if (world->isPixelVisible(pos)) return false;

	speed += accel * frameClock;
	pos   += speed * frameClock;

	sprite->setPosition(pos);
	app->draw(*sprite);

	return true;
}



/***********************************************************************
     * Weather
     * constructor

***********************************************************************/
fired::Weather::Weather(fired::World *_world) {
	world = _world;
	cam   = world->cam;
}



/***********************************************************************
     * Weather
     * destructor

***********************************************************************/
fired::Weather::~Weather() {
	deleteList(particles);
	delete sprite;
}



/***********************************************************************
     * Weather
     * render

***********************************************************************/
void fired::Weather::render() {
	unsigned int i = 0;

	while (i < particles.size())
		if (!particles[i]->process(world)) {
			delete particles[i];
			particles.erase(particles.begin() + i);
		} else
			i++;
}



/***********************************************************************
     * Weather
     * update

***********************************************************************/
void fired::Weather::update() {
	render();
}
