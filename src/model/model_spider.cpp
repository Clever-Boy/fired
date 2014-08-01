/***********************************************************************
     * File       : model_spider.cpp
     * Created    : Jul 31, 2014
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#include "game.hpp"



/***********************************************************************
     * ModelSpider
     * constructor

***********************************************************************/
fired::ModelSpider::ModelSpider(fired::Character *_owner, fired::BaseModelSpider *_base, fired::ModelSpiderColors *modelColors, float scale, fired::World *_world) {
	owner    = _owner;
	world    = _world;
	base     = _base;

	modelScale       = scale;
	owner->phys.size = base->size * scale;
	owner->phys.calculate();

	updateParts(modelColors);
	updateBones();
	respawn();
}



/***********************************************************************
     * ModelSpider
     * updateAnimation

***********************************************************************/
void fired::ModelSpider::updateAnimation() {
	if (owner->dead) {
		if (bodyAnimation != caNone) bodyAnimation = caNone;
	} else {
		bodyAnimation = caNone;

		if (owner->phys.isMoving)  bodyAnimation = caMoving;
		if (!owner->phys.onGround) bodyAnimation = caJumping;
	}
}



/***********************************************************************
     * ModelSpider
     * updateParts

***********************************************************************/
void fired::ModelSpider::updateParts(fired::ModelSpiderColors *modelColors) {
	initPart(&partHead  , &base->partHead  , modelColors->partHead  , NULL, &owner->direction);
	initPart(&partBody  , &base->partBody  , modelColors->partBody  , NULL, &owner->direction);
	initPart(&partLegsF1, &base->partLegsF1, modelColors->partLegsF1, NULL, &owner->direction);
	initPart(&partLegsF2, &base->partLegsF2, modelColors->partLegsF2, NULL, &owner->direction);
	initPart(&partLegsF3, &base->partLegsF3, modelColors->partLegsF3, NULL, &owner->direction);
	initPart(&partLegsF4, &base->partLegsF4, modelColors->partLegsF4, NULL, &owner->direction);
	initPart(&partShoeF1, &base->partShoeF1, modelColors->partShoeF1, NULL, &owner->direction);
	initPart(&partShoeF2, &base->partShoeF2, modelColors->partShoeF2, NULL, &owner->direction);
	initPart(&partShoeF3, &base->partShoeF3, modelColors->partShoeF3, NULL, &owner->direction);
	initPart(&partShoeF4, &base->partShoeF4, modelColors->partShoeF4, NULL, &owner->direction);
}



/***********************************************************************
     * ModelSpider
     * updateBones

***********************************************************************/
void fired::ModelSpider::updateBones() {
	initBone(&bones.legsF1, partLegsF1.offset, partShoeF1.offset);
	initBone(&bones.legsF2, partLegsF2.offset, partShoeF2.offset);
	initBone(&bones.legsF3, partLegsF3.offset, partShoeF3.offset);
	initBone(&bones.legsF4, partLegsF4.offset, partShoeF4.offset);
	initBone(&bones.shoeF1, partShoeF1.offset, partShoeF1.offset);
	initBone(&bones.shoeF2, partShoeF2.offset, partShoeF2.offset);
	initBone(&bones.shoeF3, partShoeF3.offset, partShoeF3.offset);
	initBone(&bones.shoeF4, partShoeF4.offset, partShoeF4.offset);
}



/***********************************************************************
     * ModelSpider
     * respawn

***********************************************************************/
void fired::ModelSpider::respawn() {
	bodyParts.push_back(&partBody  );
	bodyParts.push_back(&partHead  );
	bodyParts.push_back(&partLegsF1);
	bodyParts.push_back(&partLegsF2);
	bodyParts.push_back(&partLegsF3);
	bodyParts.push_back(&partLegsF4);
	bodyParts.push_back(&partShoeF1);
	bodyParts.push_back(&partShoeF2);
	bodyParts.push_back(&partShoeF3);
	bodyParts.push_back(&partShoeF4);

	bodyAnimation     = caNone;
	bodyAnimationTime = 0;
}



/***********************************************************************
     * ModelSpider
     * processBones

***********************************************************************/
void fired::ModelSpider::processBones() {
	partLegsF1.animOffset = bones.legsF1.getOriginOffset();
	partLegsF2.animOffset = bones.legsF2.getOriginOffset();
	partLegsF3.animOffset = bones.legsF3.getOriginOffset();
	partLegsF4.animOffset = bones.legsF4.getOriginOffset();

	partLegsF1.animRotation = bones.legsF1.angle;
	partLegsF2.animRotation = bones.legsF2.angle;
	partLegsF3.animRotation = bones.legsF3.angle;
	partLegsF4.animRotation = bones.legsF4.angle;

	partShoeF1.animOffset = bones.legsF1.getEndOffset();
	partShoeF2.animOffset = bones.legsF2.getEndOffset();
	partShoeF3.animOffset = bones.legsF3.getEndOffset();
	partShoeF4.animOffset = bones.legsF4.getEndOffset();

	partShoeF1.animRotation = bones.shoeF1.angle;
	partShoeF2.animRotation = bones.shoeF2.angle;
	partShoeF3.animRotation = bones.shoeF3.angle;
	partShoeF4.animRotation = bones.shoeF4.angle;
}



/***********************************************************************
     * ModelSpider
     * processAnimation

***********************************************************************/
void fired::ModelSpider::processAnimation() {
	switch (bodyAnimation) {
		case caNone:
		case caJumping:
		case caShooting:
		case caMeleeAttack:
		case caBroadAttack:
			bodyAnimationTime = 0.0;

			bones.legsF1.rotate(-40);
			bones.legsF2.rotate(-20);
			bones.legsF3.rotate( 20);
			bones.legsF4.rotate( 40);

			bones.shoeF1.rotate( 20);
			bones.shoeF2.rotate( 20);
			bones.shoeF3.rotate(-20);
			bones.shoeF4.rotate(-20);
			break;


		case caMoving:
			bodyAnimationTime += frameClock * abs(owner->phys.velocity.x);
			bodyFrame          = (int)(bodyAnimationTime / 5) % 14;

			bones.legsF1.rotate(-40);
			bones.legsF2.rotate(-20);
			bones.legsF3.rotate( 20);
			bones.legsF4.rotate( 40);

			bones.shoeF1.rotate( 20);
			bones.shoeF2.rotate( 20);
			bones.shoeF3.rotate(-20);
			bones.shoeF4.rotate(-20);

			break;
	}
}
