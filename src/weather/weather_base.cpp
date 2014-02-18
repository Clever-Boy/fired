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
	if (!world->isPixelVisible(pos)) return false;

	speed += accel * frameClock;
	pos   += speed * frameClock;

	sprite->setPosition(pos);
	sprite->setScale(scale, scale);
	app->draw(*sprite);

	return true;
}



/***********************************************************************
     * Weather
     * constructor

***********************************************************************/
fired::Weather::Weather(fired::World *_world, float _frequency, float _wind) {
	world = _world;
	cam   = world->cam;

	life      = 0;
	frequency = _frequency;
	wind      = _wind;

	if (wind < -45.0) wind = -45.0;
	if (wind >  45.0) wind =  45.0;
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
	unsigned int count = cam->viewport.height / (2.0 * speed.y * frequency);

	while (count-- > 0) {
		particles.push_back(new fired::WeatherParticle);
		particles.back()->sprite   = sprite;
		particles.back()->speed    = speed;
		particles.back()->accel    = accel;
		particles.back()->scale    = genScale();
		particles.back()->pos      = cam->offset + sf::Vector2f(random() % settings->window.width, random() % settings->window.height);
	}
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
	particles.back()->scale    = genScale();
	particles.back()->pos      = genPos();
}



/***********************************************************************
     * Weather
     * genPos

***********************************************************************/
sf::Vector2f fired::Weather::genPos() {
	unsigned int random_val = random() % (settings->window.width + 2 * settings->window.height);
	sf::Vector2f result = cam->offset;

	if (random_val < settings->window.height)
		result += sf::Vector2f(1, random_val);
	else if (random_val < settings->window.height + settings->window.width)
		result += sf::Vector2f(random_val - settings->window.height, 0);
	else
		result += sf::Vector2f(settings->window.width - 1, random_val - (settings->window.width + settings->window.height));

	return result;
}
