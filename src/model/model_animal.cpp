/***********************************************************************
     * File       : model_animal.cpp
     * Created    : Jul 30, 2014
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#include "game.hpp"



/***********************************************************************
     * ModelAnimal
     * constructor

***********************************************************************/
fired::ModelAnimal::ModelAnimal(fired::Character *_owner, fired::BaseModelAnimal *_base, fired::ModelAnimalColors *modelColors, float scale, fired::World *_world) {
	owner    = _owner;
	world    = _world;
	base     = _base;

	modelScale       = scale;
	legsDiff         = abs(base->partLegsBF.offset.x - base->partLegsFF.offset.x);
	owner->phys.size = base->size * scale;
	owner->phys.calculate();

	updateParts(modelColors);
	updateBones();
	respawn();
}



/***********************************************************************
     * ModelAnimal
     * updateAnimation

***********************************************************************/
void fired::ModelAnimal::updateAnimation() {
	if (owner->dead) {
		if (bodyAnimation != caNone) bodyAnimation = caNone;
	} else {
		bodyAnimation = caNone;

		if (owner->phys.isMoving)  bodyAnimation = caMoving;
		if (!owner->phys.onGround) bodyAnimation = caJumping;
	}
}



/***********************************************************************
     * ModelAnimal
     * updateParts

***********************************************************************/
void fired::ModelAnimal::updateParts(fired::ModelAnimalColors *modelColors) {
	initPart(&partHead  , &base->partHead  , modelColors->partHead  , NULL, &owner->direction);
	initPart(&partBody  , &base->partBody  , modelColors->partBody  , NULL, &owner->direction);
	initPart(&partTail  , &base->partTail  , modelColors->partTail  , NULL, &owner->direction);
	initPart(&partLegsFF, &base->partLegsFF, modelColors->partLegsFF, NULL, &owner->direction);
	initPart(&partLegsBF, &base->partLegsBF, modelColors->partLegsBF, NULL, &owner->direction);
	initPart(&partLegsFB, &base->partLegsFB, modelColors->partLegsFB, NULL, &owner->direction);
	initPart(&partLegsBB, &base->partLegsBB, modelColors->partLegsBB, NULL, &owner->direction);
}



/***********************************************************************
     * ModelAnimal
     * updateBones

***********************************************************************/
void fired::ModelAnimal::updateBones() {
	initBone(&bones.legsFF, partLegsFF.offset, partLegsFF.offset);
	initBone(&bones.legsBF, partLegsBF.offset, partLegsBF.offset);
	initBone(&bones.legsFB, partLegsFB.offset, partLegsFB.offset);
	initBone(&bones.legsBB, partLegsBB.offset, partLegsBB.offset);
	initBone(&bones.tail  , partTail.offset  , partTail.offset);
}



/***********************************************************************
     * ModelAnimal
     * respawn

***********************************************************************/
void fired::ModelAnimal::respawn() {
	bodyParts.push_back(&partLegsBF);
	bodyParts.push_back(&partLegsBB);
	bodyParts.push_back(&partBody  );
	bodyParts.push_back(&partHead  );
	bodyParts.push_back(&partTail  );
	bodyParts.push_back(&partLegsFF);
	bodyParts.push_back(&partLegsFB);

	bodyAnimation     = caNone;
	bodyAnimationTime = 0;
}



/***********************************************************************
     * ModelAnimal
     * processBones

***********************************************************************/
void fired::ModelAnimal::processBones() {
	partLegsFF.animOffset   = bones.legsFF.getOriginOffset();
	partLegsFF.animRotation = bones.legsFF.angle;

	partLegsBF.animOffset   = bones.legsBF.getOriginOffset();
	partLegsBF.animRotation = bones.legsBF.angle;

	partLegsFB.animOffset   = bones.legsFB.getOriginOffset();
	partLegsFB.animRotation = bones.legsFB.angle;

	partLegsBB.animOffset   = bones.legsBB.getOriginOffset();
	partLegsBB.animRotation = bones.legsBB.angle;

	partTail.animOffset   = bones.tail.getEndOffset();
	partTail.animRotation = bones.tail.angle;
}



/***********************************************************************
     * ModelAnimal
     * processAnimation

***********************************************************************/
void fired::ModelAnimal::processAnimation() {
	switch (bodyAnimation) {
		case caNone:
		case caShooting:
		case caMeleeAttack:
		case caBroadAttack:
			bodyAnimationTime = 0.0;
			break;


		case caMoving:
			bodyAnimationTime += frameClock * abs(owner->phys.velocity.x);
			bodyFrame          = (int)(bodyAnimationTime / 5) % 14;

			{
				float xOffset = legsDiff * sin(3.14f * bodyFrame / 14);
				float yOffset = legsDiff * sin(3.14f * bodyFrame / 7) / 2.5f;
				float angle   = cos(3.14f * bodyFrame / 7) * 15.0f;

				bones.legsFF.move(sf::Vector2f( xOffset, lessOrZero(-yOffset)));
				bones.legsBF.move(sf::Vector2f(-xOffset, lessOrZero( yOffset)));
				bones.legsFB.move(sf::Vector2f(-xOffset, lessOrZero( yOffset)));
				bones.legsBB.move(sf::Vector2f( xOffset, lessOrZero(-yOffset)));

				bones.legsFF.rotate( angle);
				bones.legsBF.rotate(-angle);
				bones.legsFB.rotate(-angle);
				bones.legsBB.rotate( angle);
				bones.tail.rotate(angle);
			}
			break;


		case caJumping:
			bodyAnimationTime = 0.0;

			bones.legsFF.rotate( 20);
			bones.legsBF.rotate(-20);
			bones.legsFB.rotate(-20);
			bones.legsBB.rotate( 20);
			bones.tail.rotate(20);
			break;
	}
}
