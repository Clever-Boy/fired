#include "game.hpp"

//======================================================================


void fired::Chunk::init(fired::Bodypart *bodyPart, float scale, sf::Vector2f position) {
	base = bodyPart->base;
	scaleX = *bodyPart->direction * scale;
	scaleY = scale;
	pos = position;

	rotation = 0;
	rotationSpeed = 0;
	speed = sf::Vector2f(0, 0);
}

//======================================================================


void fired::Chunk::update(sf::RenderWindow *app) {
	pos += speed * frameClock;
	rotation += rotationSpeed * frameClock;

	render(app);
}

//======================================================================


void fired::Chunk::render(sf::RenderWindow *app) {
	base->chunk->setScale(scaleX, scaleY);
	base->chunk->setRotation(rotation);
	base->chunk->setPosition(pos);
	app->draw(*base->chunk);
}
