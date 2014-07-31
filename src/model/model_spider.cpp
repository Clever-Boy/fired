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
	initPart(&partLegsB1, &base->partLegsB1, modelColors->partLegsB1, NULL, &owner->direction);
	initPart(&partLegsB2, &base->partLegsB2, modelColors->partLegsB2, NULL, &owner->direction);
	initPart(&partLegsB3, &base->partLegsB3, modelColors->partLegsB3, NULL, &owner->direction);
	initPart(&partLegsB4, &base->partLegsB4, modelColors->partLegsB4, NULL, &owner->direction);
	initPart(&partShoeF1, &base->partShoeF1, modelColors->partShoeF1, NULL, &owner->direction);
	initPart(&partShoeF2, &base->partShoeF2, modelColors->partShoeF2, NULL, &owner->direction);
	initPart(&partShoeF3, &base->partShoeF3, modelColors->partShoeF3, NULL, &owner->direction);
	initPart(&partShoeF4, &base->partShoeF4, modelColors->partShoeF4, NULL, &owner->direction);
	initPart(&partShoeB1, &base->partShoeB1, modelColors->partShoeB1, NULL, &owner->direction);
	initPart(&partShoeB2, &base->partShoeB2, modelColors->partShoeB2, NULL, &owner->direction);
	initPart(&partShoeB3, &base->partShoeB3, modelColors->partShoeB3, NULL, &owner->direction);
	initPart(&partShoeB4, &base->partShoeB4, modelColors->partShoeB4, NULL, &owner->direction);
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
	initBone(&bones.legsB1, partLegsB1.offset, partShoeB1.offset);
	initBone(&bones.legsB2, partLegsB2.offset, partShoeB2.offset);
	initBone(&bones.legsB3, partLegsB3.offset, partShoeB3.offset);
	initBone(&bones.legsB4, partLegsB4.offset, partShoeB4.offset);
	initBone(&bones.shoeF1, partShoeF1.offset, partShoeF1.offset);
	initBone(&bones.shoeF2, partShoeF2.offset, partShoeF2.offset);
	initBone(&bones.shoeF3, partShoeF3.offset, partShoeF3.offset);
	initBone(&bones.shoeF4, partShoeF4.offset, partShoeF4.offset);
	initBone(&bones.shoeB1, partShoeB1.offset, partShoeB1.offset);
	initBone(&bones.shoeB2, partShoeB2.offset, partShoeB2.offset);
	initBone(&bones.shoeB3, partShoeB3.offset, partShoeB3.offset);
	initBone(&bones.shoeB4, partShoeB4.offset, partShoeB4.offset);
}



/***********************************************************************
     * ModelSpider
     * respawn

***********************************************************************/
void fired::ModelSpider::respawn() {
	bodyParts.push_back(&partShoeB1);
	bodyParts.push_back(&partShoeB2);
	bodyParts.push_back(&partShoeB3);
	bodyParts.push_back(&partShoeB4);
	bodyParts.push_back(&partLegsB1);
	bodyParts.push_back(&partLegsB2);
	bodyParts.push_back(&partLegsB3);
	bodyParts.push_back(&partLegsB4);
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
	return;
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
			break;


		case caMoving:
			bodyAnimationTime += frameClock * abs(owner->phys.velocity.x);
			bodyFrame          = (int)(bodyAnimationTime / 5) % 14;
			break;
	}
}
