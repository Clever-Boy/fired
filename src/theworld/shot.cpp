#include "game.hpp"

//======================================================================


void fired::Shot::init(sf::Vector2f _pos, float _angle, float speed, fired::Character *_owner) {
	pos      = _pos;
	owner    = _owner;
	angle    = _angle;

	velocity = sf::Vector2f(speed * cos(angle), speed * sin(angle));
	line = sf::VertexArray(sf::Lines, 2);
}

//======================================================================


void fired::Shot::deinit() {
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
	line[1].position = pos + velocity * frameClock;
	app->draw(line);
}
