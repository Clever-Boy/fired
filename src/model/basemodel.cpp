#include "game.hpp"

//======================================================================


fired::Model::~Model() {
	bodyParts.clear();
}

//======================================================================


void fired::Model::render() {
	for (unsigned int i = 0; i < bodyParts.size(); i++) drawPart(bodyParts[i]);
}

//======================================================================


void fired::Model::explode(sf::Vector2f shot, float knockback) {
	for (unsigned int i = 0; i < bodyParts.size(); i++) chunkPart(bodyParts[i], shot, knockback / 10);
	bodyParts.clear();
}

//======================================================================


void fired::Model::initPart(fired::Bodypart *part, fired::BaseBodypart *base, sf::Color color, sf::Vector2f offset, int *direction) {
	part->base         = base;
	part->color        = color;
	part->offset       = offset;
	part->direction    = direction;
	part->animOffset   = sf::Vector2f(0.0, 0.0);
	part->animRotation = 0.0;
}

//======================================================================


void fired::Model::drawPart(fired::Bodypart *part) {
	part->base->sprite->setScale(*part->direction * modelScale, modelScale);
	part->base->sprite->setRotation(*part->direction * part->animRotation);
	part->base->sprite->setColor(part->color);

	if (*part->direction == 1)
		part->base->sprite->setPosition(owner->phys.pos + (part->offset + part->animOffset) * modelScale);
	else
		part->base->sprite->setPosition(owner->phys.pos + sf::Vector2f(-part->offset.x - part->animOffset.x, part->offset.y + part->animOffset.y) * modelScale + sf::Vector2f(owner->phys.size.x, 0));

	app->draw(*part->base->sprite);
}

//======================================================================


void fired::Model::chunkPart(fired::Bodypart *part, sf::Vector2f shot, float knockback) {
	sf::Vector2f chunkPos;
	if (*part->direction == 1)
		chunkPos = owner->phys.pos + (part->offset + part->base->size / 2.0f) * modelScale;
	else
		chunkPos = owner->phys.pos + sf::Vector2f(-part->offset.x - part->base->size.x / 2.0f, part->offset.y + part->base->size.y / 2.0f) * modelScale + sf::Vector2f(owner->phys.size.x, 0);


	world->addChunk(part, modelScale, chunkPos, vNorm(part->offset - part->base->origin - shot) * knockback * 10.0f);
}

//======================================================================


void fired::Model::resetPart(fired::Bodypart *part) {
	part->animOffset   = sf::Vector2f(0, 0);
	part->animRotation = 0;
}

//======================================================================


void fired::Model::resetAnimation() {
	for (unsigned int i = 0; i < bodyParts.size(); i++) resetPart(bodyParts[i]);
}

