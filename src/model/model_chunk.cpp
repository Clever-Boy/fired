/***********************************************************************
     * File       : model_chunk.cpp
     * Created    : Aug 09, 2013
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#include "game.hpp"



/***********************************************************************
     * Chunk
     * constructor

***********************************************************************/
fired::Chunk::Chunk(fired::Bodypart *bodyPart, float scale, sf::Vector2f position, sf::Vector2f speed, fired::World *_world) {
	base   = bodyPart->base;
	color  = bodyPart->color;
	scaleX = *bodyPart->direction * scale;
	scaleY = scale;
	world  = _world;

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



/***********************************************************************
     * Chunk
     * update

***********************************************************************/
bool fired::Chunk::update() {
	if (phys.onGround) {
		phys.velocity.x -= sign(phys.velocity.x) * PHYS_FRICTION_ACCEL * frameClock / 3.0;
		rotationSpeed -= sign(rotationSpeed) * frameClock;
	}

	if ((lifetime += frameClock) > CHUNK_LIFETIME) return false;
	rotationSpeed = phys.velocity.x * 6.0;

	if (abs(phys.velocity.x) < PHYS_EPSILON) phys.velocity.x = 0;
	if (abs(rotationSpeed)   < PHYS_EPSILON) rotationSpeed   = 0;

	rotation += rotationSpeed * frameClock;
	if (world->isRectVisible(phys.rect)) render();

	return true;
}



/***********************************************************************
     * Chunk
     * render

***********************************************************************/
void fired::Chunk::render() {
	if (lifetime > CHUNK_DISAPPEARTIME) color.a = 255 * (CHUNK_LIFETIME - lifetime) / (CHUNK_LIFETIME - CHUNK_DISAPPEARTIME);

	base->sprite->setColor(color);
	base->sprite->setOrigin(base->size / 2.0f);
	base->sprite->setScale(scaleX, scaleY);
	base->sprite->setRotation(rotation);
	base->sprite->setPosition(phys.pos);
	app->draw(*base->sprite);
}
