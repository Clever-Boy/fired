/***********************************************************************
     * File       : model_base.cpp
     * Created    : Aug 08, 2013
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#include "game.hpp"



/***********************************************************************
     * Model
     * constructor

***********************************************************************/
fired::Model::~Model() {
	bodyParts.clear();
	bodyBones.clear();
}



/***********************************************************************
     * Model
     * render

***********************************************************************/
void fired::Model::render() {
	for (unsigned int i = 0; i < bodyParts.size(); i++) drawPart(bodyParts[i]);
}



/***********************************************************************
     * Model
     * update

***********************************************************************/
void fired::Model::update() {
	updateAnimation();
	resetAnimation();
	processAnimation();
	processBones();
}



/***********************************************************************
     * Model
     * explode

***********************************************************************/
void fired::Model::explode(sf::Vector2f shot, float knockback) {
	for (unsigned int i = 0; i < bodyParts.size(); i++) chunkPart(bodyParts[i], shot, knockback / 10);
	bodyParts.clear();
}



/***********************************************************************
     * Model
     * initPart

***********************************************************************/
void fired::Model::initPart(fired::Bodypart *part, fired::BaseModelBodypart *base, sf::Color color, fired::BaseArmor *armor, int *direction) {
	if (armor) {
		part->base  = armor->base;
		part->color = armor->color;
	} else {
		part->base  = base->part;
		part->color = color;
	}

	part->offset       = base->offset;
	part->direction    = direction;
	part->animOffset   = sf::Vector2f(0.0, 0.0);
	part->animRotation = 0.0;
}



/***********************************************************************
     * Model
     * initBone

***********************************************************************/
void fired::Model::initBone(fired::ModelBone *bone, sf::Vector2f start, sf::Vector2f end) {
	bone->set(start, end);
	bodyBones.push_back(bone);
}



/***********************************************************************
     * Model
     * drawPart

***********************************************************************/
void fired::Model::drawPart(fired::Bodypart *part) {
	if (!part->base) return;

	part->base->sprite->setOrigin(part->base->origin);
	part->base->sprite->setScale(*part->direction * modelScale, modelScale);
	part->base->sprite->setRotation(*part->direction * part->animRotation);
	part->base->sprite->setColor(part->color);

	if (*part->direction == 1)
		part->base->sprite->setPosition(owner->phys.pos + (part->offset + part->animOffset) * modelScale);
	else
		part->base->sprite->setPosition(owner->phys.pos + sf::Vector2f(-part->offset.x - part->animOffset.x, part->offset.y + part->animOffset.y) * modelScale + sf::Vector2f(owner->phys.size.x, 0));

	app->draw(*part->base->sprite);
}



/***********************************************************************
     * Model
     * chunkPart

***********************************************************************/
void fired::Model::chunkPart(fired::Bodypart *part, sf::Vector2f shot, float knockback) {
	if (!part->base) return;

	sf::Vector2f chunkPos;
	sf::Vector2f chunkSpeed;

	if (*part->direction == 1)
		chunkPos = owner->phys.pos + (part->offset + part->base->size / 2.0f) * modelScale;
	else
		chunkPos = owner->phys.pos + sf::Vector2f(-part->offset.x - part->base->size.x / 2.0f, part->offset.y + part->base->size.y / 2.0f) * modelScale + sf::Vector2f(owner->phys.size.x, 0);

	chunkSpeed = owner->phys.velocity + vNorm(part->offset - part->base->origin - shot) * knockback * 20.0f;

	world->addChunk(part, modelScale, chunkPos, chunkSpeed);
	world->addBloodSplash(chunkPos, -chunkSpeed, 20);
}



/***********************************************************************
     * Model
     * resetPart

***********************************************************************/
void fired::Model::resetPart(fired::Bodypart *part) {
	if (!part->base) return;

	part->animOffset   = sf::Vector2f(0, 0);
	part->animRotation = 0;
}



/***********************************************************************
     * Model
     * resetAnimation

***********************************************************************/
void fired::Model::resetAnimation() {
	for (unsigned int i = 0; i < bodyParts.size(); i++) resetPart(bodyParts[i]);
	for (unsigned int i = 0; i < bodyBones.size(); i++) bodyBones[i]->reset();
}

