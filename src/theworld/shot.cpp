#include "game.hpp"

//======================================================================


fired::Shot::Shot(sf::Vector2f _pos, float _angle, float speed, fired::Character *_owner) {
	pos       = _pos;
	owner     = _owner;
	angle     = _angle;
	damage    = owner->getDamage();
	knockback = owner->getKnockback();

	velocity = sf::Vector2f(speed * cos(angle), speed * sin(angle));
	line = sf::VertexArray(sf::Lines, 2);
	line[0].color = sf::Color::White;
	line[1].color = sf::Color(150, 150, 150, 50);
}

//======================================================================


fired::Shot::~Shot() {
	return;
}

//======================================================================


bool fired::Shot::update(sf::RenderWindow *app) {
	pos += velocity * frameClock;
	render(app);
	return true;
}

//======================================================================


void fired::Shot::render(sf::RenderWindow *app) {
	line[0].position = pos;
	line[1].position = pos - velocity * frameClock;
	app->draw(line);
}
