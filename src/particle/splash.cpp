#include "game.hpp"

//======================================================================


void fired::ParticleSystemSplash::init(sf::Vector2f pos, sf::Vector2f direction, sf::Color color, float size, int count, float lifetime, float _endScale) {
	sprite = new sf::RectangleShape(sf::Vector2f(size, size));

	sf::Vector2f normal(direction.y, -direction.x);
	sf::Vector2f accel(0, PHYS_GRAVITY / 2);
	endScale = _endScale;

	for (int i = 0; i < count; i++) {
		particles.push_back(new fired::Particle);
		particles.back()->color    = color;
		particles.back()->sprite   = sprite;
		particles.back()->pos      = pos;
		particles.back()->scale    = 1;
		particles.back()->speed    = direction * (float)((random() % 400) / 400.0) + normal * (float)(((random() % 400) - 200) / 400.0);
		particles.back()->accel    = accel;
		particles.back()->life     = 0;
		particles.back()->lifetime = lifetime;
	}

	return;
}

//======================================================================


bool fired::ParticleSystemSplash::update(sf::RenderWindow *app) {
	for (unsigned int i = 0; i < particles.size(); i++)
		particles[i]->scale = endScale + (1 - endScale) * (particles[i]->lifetime - particles[i]->life) / particles[i]->lifetime;

	if (particles.size() == 0) return false;
	render(app);
	return true;
}

//======================================================================


void fired::ParticleSystemSplash::deinit() {
	baseDeinit();
	delete sprite;
}
