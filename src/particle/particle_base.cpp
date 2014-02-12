/***********************************************************************
     * File       : particle_base.cpp
     * Created    : Aug 02, 2013
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#include "game.hpp"



/***********************************************************************
     * Particle
     * process

***********************************************************************/
bool fired::Particle::process(fired::World *world, bool physical) {
	life += frameClock;
	if (life > lifetime) return false;

	if (physical) if (world->isSolidPixel(pos)) {
		speed = sf::Vector2f(0, 0);
		accel = sf::Vector2f(0, 0);
	}

	speed += accel * frameClock;
	pos += speed * frameClock;

	if (world->isPixelVisible(pos)) {
		sprite->setPosition(pos);
		sprite->setFillColor(color);
		sprite->setScale(scale, scale);
		app->draw(*sprite);
	}

	return true;
}



/***********************************************************************
     * ParticleSystem
     * destructor

***********************************************************************/
fired::ParticleSystem::~ParticleSystem() {
	deleteList(particles);
	delete sprite;
}



/***********************************************************************
     * ParticleSystem
     * render

***********************************************************************/
void fired::ParticleSystem::render() {
	unsigned int i = 0;

	while (i < particles.size())
		if (!particles[i]->process(world, physical)) {
			delete particles[i];
			particles.erase(particles.begin() + i);
		} else
			i++;
}



/***********************************************************************
     * ParticleSystem
     * update

***********************************************************************/
bool fired::ParticleSystem::update() {
	render();
	return false;
}
