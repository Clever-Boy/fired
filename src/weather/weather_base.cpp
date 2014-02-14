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
fired::Weather::Weather(fired::World *_world, float _frequency, sf::Vector2f _speed) {
	world = _world;
	cam   = world->cam;

	life      = 0;
	speed     = _speed;
	frequency = _frequency;
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
	for (life += frameClock; life > frequency; life -= frequency) addParticle();
	render();
}



/***********************************************************************
     * Weather
     * fill

***********************************************************************/
void fired::Weather::fill() {
	addParticle();
}



/***********************************************************************
     * Weather
     * addParticle

***********************************************************************/
void fired::Weather::addParticle() {
	particles.push_back(new fired::WeatherParticle);
	particles.back()->sprite   = sprite;
	particles.back()->speed    = speed;
	particles.back()->accel    = accel;
	particles.back()->pos      = cam->offset + sf::Vector2f(random() % settings->window.width, 0);
}
