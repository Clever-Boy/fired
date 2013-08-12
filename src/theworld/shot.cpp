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
	line[1].color = sf::Color(141, 152, 141, 50);
}

//======================================================================


fired::Shot::~Shot() {
	return;
}

//======================================================================


void fired::Shot::update() {
	pos += velocity * frameClock;
	render();
}

//======================================================================


void fired::Shot::render() {
	line[0].position = pos;
	line[1].position = pos - velocity * frameClock;
	app->draw(line);
}
