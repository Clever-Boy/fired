#include "game.hpp"

//======================================================================


bool fired::Particle::process(fired::World *world, bool physical) {
	life += frameClock;
	if (life > lifetime) return false;

	if (physical) if (world->isSolidPixel(pos)) {
		speed = sf::Vector2f(0, 0);
		accel = sf::Vector2f(0, 0);
	}

	speed += accel * frameClock;
	pos += speed * frameClock;

	sprite->setPosition(pos);
	sprite->setFillColor(color);
	sprite->setScale(scale, scale);
	app->draw(*sprite);
	return true;
}

//======================================================================


void fired::ParticleSystem::render() {
	unsigned int i = 0;

	while (i < particles.size())
		if (!particles[i]->process(world, physical)) {
			delete particles[i];
			particles.erase(particles.begin() + i);
		} else
			i++;
}

//======================================================================


bool fired::ParticleSystem::update() {
	render();
	return false;
}

//======================================================================


fired::ParticleSystem::~ParticleSystem() {
	deleteList(particles);
}
