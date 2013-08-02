#include "game.hpp"

//======================================================================


void fired::Shot::init(sf::Vector2f _pos, float angle, float speed, fired::Character *_owner) {
	pos = _pos;
	velocity = sf::Vector2f(speed * cos(angle), speed * sin(angle));
	owner = _owner;

	line = new sf::RectangleShape(sf::Vector2f(50, 1));
	line->setRotation(angle * 180.0 / 3.14);
}

//======================================================================


void fired::Shot::deinit() {
	delete line;
}

//======================================================================


bool fired::Shot::update(sf::RenderWindow *app) {
	pos += velocity * frameClock;

	if (pos.x > 10000 || pos.x < 0) return false;
	if (pos.y > 10000 || pos.y < 0) return false;

	render(app);
	return true;
}

//======================================================================


void fired::Shot::render(sf::RenderWindow *app) {
	line->setPosition(pos);
	app->draw(*line);
}
