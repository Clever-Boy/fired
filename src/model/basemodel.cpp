#include "game.hpp"

//======================================================================


void fired::Model::deinit() {
	bodyParts.clear();
}

//======================================================================


void fired::Model::render() {
	for (unsigned int i = 0; i < bodyParts.size(); i++) drawPart(bodyParts[i]);
}

//======================================================================


void fired::Model::explode() {
	for (unsigned int i = 0; i < bodyParts.size(); i++) chunkPart(bodyParts[i]);
	bodyParts.clear();
}

//======================================================================


void fired::Model::initPart(fired::Bodypart *part, fired::BaseBodypart *base, int *direction) {
	part->base         = base;
	part->direction    = direction;
	part->animOffset   = sf::Vector2f(0.0, 0.0);
	part->animRotation = 0.0;
}

//======================================================================


void fired::Model::drawPart(fired::Bodypart *part) {
	part->base->sprite->setScale(*part->direction * modelScale, modelScale);
	part->base->sprite->setRotation(*part->direction * part->animRotation);

	if (*part->direction == 1)
		part->base->sprite->setPosition(owner->phys.pos + (part->base->offset + part->animOffset) * modelScale);
	else
		part->base->sprite->setPosition(owner->phys.pos + sf::Vector2f(-part->base->offset.x - part->animOffset.x, part->base->offset.y + part->animOffset.y) * modelScale + sf::Vector2f(owner->phys.size.x, 0));

	app->draw(*part->base->sprite);
}

//======================================================================


void fired::Model::chunkPart(fired::Bodypart *part) {
	if (*part->direction == 1)
		world->addChunk(part, modelScale, owner->phys.pos + (part->base->offset + part->base->size / 2.0f) * modelScale);
	else
		world->addChunk(part, modelScale, owner->phys.pos + sf::Vector2f(-part->base->offset.x - part->base->size.x / 2.0f, part->base->offset.y + part->base->size.y / 2.0f) * modelScale + sf::Vector2f(owner->phys.size.x, 0));
}

//======================================================================


void fired::Model::resetPart(fired::Bodypart *part) {
	part->animOffset   = sf::Vector2f(0, 0);
	part->animRotation = 0;;
}

//======================================================================


void fired::Model::resetAnimation() {
	for (unsigned int i = 0; i < bodyParts.size(); i++) resetPart(bodyParts[i]);
}

