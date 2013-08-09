#include "game.hpp"

//======================================================================


void fired::Chunk::init(fired::Bodypart *bodyPart, float scale, sf::Vector2f position, sf::Vector2f speed) {
	base = bodyPart->base;
	scaleX = *bodyPart->direction * scale;
	scaleY = scale;
	pos = position;

	phys.pos          = position;
	phys.size         = sf::Vector2f(6, 6);
	phys.velocity     = speed;
	phys.acceleration = sf::Vector2f(0, PHYS_GRAVITY / 2);
	phys.onGround     = false;
	phys.isMoving     = false;

	phys.calculate();

	rotation      = 0;
	rotationSpeed = 0;
	lifetime      = 0;
}

//======================================================================


bool fired::Chunk::update(sf::RenderWindow *app) {
	if (phys.onGround) {
		phys.velocity.x -= sign(phys.velocity.x) * PHYS_FRICTION_ACCEL * frameClock / 3.0;
		rotationSpeed -= sign(rotationSpeed) * frameClock;
	}

	if ((lifetime += frameClock) > CHUNK_LIFETIME) return false;
	rotationSpeed = phys.velocity.x * 12.0;

	if (abs(phys.velocity.x) < PHYS_EPSILON) phys.velocity.x = 0;
	if (abs(rotationSpeed)   < PHYS_EPSILON) rotationSpeed   = 0;

	phys.pos += phys.velocity * frameClock;
	rotation += rotationSpeed * frameClock;

	render(app);
	return true;
}

//======================================================================


void fired::Chunk::render(sf::RenderWindow *app) {
	base->chunk->setColor(sf::Color(255, 255, 255, 255));
	if (lifetime > CHUNK_DISAPPEARTIME) base->chunk->setColor(sf::Color(255, 255, 255, 255 * (CHUNK_LIFETIME - lifetime) / (CHUNK_LIFETIME - CHUNK_DISAPPEARTIME)));

	base->chunk->setScale(scaleX, scaleY);
	base->chunk->setRotation(rotation);
	base->chunk->setPosition(phys.pos);
	app->draw(*base->chunk);
}
