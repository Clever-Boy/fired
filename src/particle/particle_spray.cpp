/***********************************************************************
     * File       : particle_spray.cpp
     * Created    : Feb 11, 2014
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#include "game.hpp"



/***********************************************************************
     * ParticleSystemSpray
     * constructor

***********************************************************************/
fired::ParticleSystemSpray::ParticleSystemSpray(sf::Vector2f _pos, sf::Vector2f _direction, fired::World *_world, sf::Color _color, float _size, float _frequency, float _lifetime, float _endScale, bool _physical, sf::Vector2f *_follow = NULL) {
	active    = true;
	life      = 0;
	endScale  = _endScale;
	physical  = _physical;
	frequency = _frequency;
	world     = _world;
	pos       = _pos;
	color     = _color;
	lifetime  = _lifetime;
	size      = _size;
	direction = _direction;
	follow    = _follow;

	normal = sf::Vector2f(direction.y, -direction.x);
	accel  = sf::Vector2f(0, PHYS_GRAVITY / 2);

	sprite = new sf::RectangleShape(sf::Vector2f(size, size));
	sprite->setOrigin(sf::Vector2f(size / 2, size / 2));
}



/***********************************************************************
     * ParticleSystemSpray
     * update

***********************************************************************/
bool fired::ParticleSystemSpray::update() {
	life += frameClock;

	if (active) while (life > frequency) {
		life -= frequency;
		addParticle();
	}

	for (unsigned int i = 0; i < particles.size(); i++)
		particles[i]->scale = endScale + (1 - endScale) * (particles[i]->lifetime - particles[i]->life) / particles[i]->lifetime;

	render();
	if (particles.size() == 0 && !active) return false;
	return true;
}



/***********************************************************************
     * ParticleSystemSpray
     * addParticle

***********************************************************************/
void fired::ParticleSystemSpray::addParticle() {
	particles.push_back(new fired::Particle);
	particles.back()->color    = color;
	particles.back()->sprite   = sprite;
	particles.back()->scale    = 1.0;
	particles.back()->speed    = direction * (float)((random() % 400) / 400.0) + normal * (float)(((random() % 400) - 200) / 200.0);
	particles.back()->accel    = accel;
	particles.back()->life     = 0.0;
	particles.back()->lifetime = lifetime;

	if (follow) particles.back()->pos = *follow;
	else        particles.back()->pos = pos;
}
