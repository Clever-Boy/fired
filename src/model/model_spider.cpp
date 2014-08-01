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
