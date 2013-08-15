#include "game.hpp"

//======================================================================


fired::Shot::Shot(sf::Vector2f _pos, float _angle, float speed, fired::Character *_owner, sf::Sprite *_sprite) {
	pos       = _pos;
	owner     = _owner;
	angle     = _angle;
	sprite    = _sprite;
	damage    = owner->getDamage();
	knockback = owner->getKnockback();
	leftToFly = owner->getRange();

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


bool fired::Shot::update() {
	leftToFly -= vLen(velocity) * frameClock;
	if (leftToFly < 0) return false;

	pos += velocity * frameClock;
	render();
	return true;
}

//======================================================================


void fired::Shot::render() {
	if (sprite != NULL) {
		sprite->setRotation(angle * 180 / 3.14);
		sprite->setPosition(pos);
		app->draw(*sprite);
	} else {
		line[0].position = pos;
		line[1].position = pos - velocity * frameClock;
		app->draw(line);
	}
}

//======================================================================


fired::MeleeShot::MeleeShot(sf::FloatRect _shot, sf::Vector2f _normal, fired::Character *_owner) {
	shot      = _shot;
	owner     = _owner;
	normal    = _normal;
	damage    = owner->getDamage();
	knockback = owner->getKnockback();
}

//======================================================================


fired::MeleeShot::~MeleeShot() {
	return;
}

