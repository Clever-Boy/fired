#include "game.hpp"

//======================================================================


bool fired::Particle::process(sf::RenderWindow *app) {
	life += frameClock;
	if (life > lifetime) return false;

	speed += accel * frameClock;
	pos += speed * frameClock;

	sprite->setPosition(pos);
	sprite->setFillColor(color);
	sprite->setScale(scale, scale);
	app->draw(*sprite);
	return true;
}

//======================================================================


void fired::ParticleSystem::render(sf::RenderWindow *app) {
	int i = 0;

	while (i < particles.size())
		if (!particles[i]->process(app)) {
			delete particles[i];
			particles.erase(particles.begin() + i);
		} else
			i++;
}

//======================================================================


void fired::ParticleSystem::baseDeinit() {
	for (int i = 0; i < particles.size(); i++)
		delete particles[i];

	particles.clear();
}
