#include "game.hpp"

//======================================================================


void fired::ParticleSystemSplash::init(sf::Vector2f pos, sf::Vector2f direction, sf::Color color) {
	sprite = new sf::RectangleShape(sf::Vector2f(2, 2));

	sf::Vector2f normal(direction.y, -direction.x);
	sf::Vector2f accel(0, PHYS_GRAVITY / 2);

	float speed_factor;

	for (int i = 0; i < 20; i++) {
		particles.push_back(new fired::Particle);
		particles.back()->color    = color;
		particles.back()->sprite   = sprite;
		particles.back()->pos      = pos;
		particles.back()->scale    = 1;
		particles.back()->speed    = direction * (float)((random() % 400) / 400.0) + normal * (float)(((random() % 400) - 200) / 400.0);
		particles.back()->accel    = accel;
		particles.back()->life     = 0;
		particles.back()->lifetime = 0.2;
	}

	return;
}

//======================================================================


bool fired::ParticleSystemSplash::update(sf::RenderWindow *app) {
	for (int i = 0; i < particles.size(); i++)
		particles[i]->scale = (particles[i]->lifetime - particles[i]->life) / particles[i]->lifetime;

	if (particles.size() == 0) return false;
	render(app);
	return true;
}

//======================================================================


void fired::ParticleSystemSplash::deinit() {
	baseDeinit();
	delete sprite;
}
