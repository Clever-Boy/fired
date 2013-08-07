#include "game.hpp"

//======================================================================


void fired::Model::deinit() {
	bodyParts.clear();
}

//======================================================================


void fired::Model::render() {
	for (int i = 0; i < bodyParts.size(); i++) drawPart(bodyParts[i]);
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


void fired::Model::resetPart(fired::Bodypart *part) {
	part->animOffset   = sf::Vector2f(0, 0);
	part->animRotation = 0;;
}

//======================================================================


void fired::Model::resetAnimation() {
	for (int i = 0; i < bodyParts.size(); i++) resetPart(bodyParts[i]);
}

