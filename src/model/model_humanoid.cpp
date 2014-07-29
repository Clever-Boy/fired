/***********************************************************************
     * File       : model_humanoid.cpp
     * Created    : Aug 08, 2013
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#include "game.hpp"



/***********************************************************************
     * ModelHumanoid
     * constructor

***********************************************************************/
fired::ModelHumanoid::ModelHumanoid(fired::Character *_owner, fired::BaseModelHumanoid *_base, fired::ModelHumanoidColors *modelColors, float scale, fired::World *_world) {
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
     * ModelHumanoid
     * update

***********************************************************************/
void fired::ModelHumanoid::update() {
	if (owner->dead) {
		if (bodyAnimation != caNone) {
			bodyAnimation = caNone;
			armsAnimation = caNone;
		}
	} else {
		bodyAnimation = caNone;
		if (armsAnimation == caShooting) armsAnimation = caNone;

		if (owner->phys.isMoving)  bodyAnimation = caMoving;
		if (!owner->phys.onGround) bodyAnimation = caJumping;

		if (owner->isShooting) {
			if (owner->weapon->type == WEAPON_TYPE_RANGED) armsAnimation = caShooting;
			if (owner->weapon->type == WEAPON_TYPE_MELEE)  armsAnimation = caMeleeAttack;
			if (owner->weapon->type == WEAPON_TYPE_BROAD)  armsAnimation = caBroadAttack;
		}
	}

	processAnimation();
}



/***********************************************************************
     * ModelHumanoid
     * updateParts

***********************************************************************/
void fired::ModelHumanoid::updateParts(fired::ModelHumanoidColors *modelColors) {
	initPart(&partHead , &base->partHead , modelColors->partHead , NULL       , &owner->watching);
	initPart(&partHair , &base->partHair , modelColors->partHair , owner->helm, &owner->watching);
	initPart(&partBody , &base->partBody , modelColors->partBody , owner->body, &owner->watching);
	initPart(&partArms , &base->partArms , modelColors->partArms , owner->arms, &owner->watching);
	initPart(&partLegsF, &base->partLegsF, modelColors->partLegsF, owner->legs, &owner->direction);
	initPart(&partLegsB, &base->partLegsB, modelColors->partLegsB, owner->legs, &owner->direction);
	initPart(&partShoeF, &base->partShoeF, modelColors->partShoeF, owner->shoe, &owner->direction);
	initPart(&partShoeB, &base->partShoeB, modelColors->partShoeB, owner->shoe, &owner->direction);
	initPart(&partFistF, &base->partFistF, modelColors->partFistF, owner->fist, &owner->watching);
	initPart(&partFistB, &base->partFistB, modelColors->partFistB, owner->fist, &owner->watching);
}



/***********************************************************************
     * ModelHumanoid
     * updateBones

***********************************************************************/
void fired::ModelHumanoid::updateBones() {
	initBone(&bones.legsF , partLegsF.offset, partShoeF.offset);
	initBone(&bones.legsB , partLegsB.offset, partShoeB.offset);
	initBone(&bones.arms  , partArms.offset , partFistF.offset);
	initBone(&bones.weapon, partFistF.offset, base->weaponOffset);
}



/***********************************************************************
     * ModelHumanoid
     * respawn

***********************************************************************/
void fired::ModelHumanoid::respawn() {
	bodyParts.push_back(&partFistB );
	bodyParts.push_back(&partLegsB );
	bodyParts.push_back(&partShoeB );
	bodyParts.push_back(&partBody  );
	bodyParts.push_back(&partHead  );
	bodyParts.push_back(&partHair  );
	bodyParts.push_back(&partLegsF );
	bodyParts.push_back(&partShoeF );
	bodyParts.push_back(&partWeapon);
	bodyParts.push_back(&partArms  );
	bodyParts.push_back(&partFistF );

	bodyAnimation = caNone;
	armsAnimation = caNone;

	bodyAnimationTime = 0;
	armsAnimationTime = 0;
}



/***********************************************************************
     * ModelHumanoid
     * setWeapon

***********************************************************************/
void fired::ModelHumanoid::setWeapon(fired::BaseWeapon *weapon) {
	partWeapon.base         = weapon->bodypart;
	partWeapon.color        = sf::Color::White;
	partWeapon.offset       = base->weaponOffset;
	partWeapon.direction    = &owner->watching;
	partWeapon.animOffset   = sf::Vector2f(0.0, 0.0);
	partWeapon.animRotation = 0.0;
}



/***********************************************************************
     * ModelHumanoid
     * processAnimation

***********************************************************************/
void fired::ModelHumanoid::processAnimation() {
	resetAnimation();
	processBodyAnimation();
	processArmsAnimation();
}



/***********************************************************************
     * ModelHumanoid
     * processBodyAnimation

***********************************************************************/
void fired::ModelHumanoid::processBodyAnimation() {
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

			partLegsF.animOffset = sf::Vector2f(cos(0.449 * bodyFrame) * 2.0 + 2.0, 0.0);
			partShoeF.animOffset = sf::Vector2f(cos(0.449 * bodyFrame) * 3.0 + 2.0, lessOrZero(sin(0.449 * bodyFrame) * 3.0));

			partLegsB.animOffset = sf::Vector2f(cos(0.449 * (bodyFrame - 7)) * 2.0 - 2.0, 0.0);
			partShoeB.animOffset = sf::Vector2f(cos(0.449 * (bodyFrame - 7)) * 3.0 - 2.0, lessOrZero(sin(0.449 * (bodyFrame - 7)) * 3.0));



			partLegsF.animOffset   = bones.legsF.getOriginOffset();
			partLegsF.animRotation = bones.legsF.angle;

			partLegsB.animOffset   = bones.legsB.getOriginOffset();
			partLegsB.animRotation = bones.legsB.angle;

			partShoeF.animOffset   = bones.legsF.getEndOffset();
			partShoeF.animRotation = bones.legsF.angle;

			partShoeB.animOffset   = bones.legsB.getEndOffset();
			partShoeB.animRotation = bones.legsB.angle;
			break;


		case caJumping:
			bodyAnimationTime = 0.0;

			bones.legsF.rotate( 20);
			bones.legsB.rotate(-20);


			partLegsF.animOffset   = bones.legsF.getOriginOffset();
			partLegsF.animRotation = bones.legsF.angle;

			partLegsB.animOffset   = bones.legsB.getOriginOffset();
			partLegsB.animRotation = bones.legsB.angle;

			partShoeF.animOffset   = bones.legsF.getEndOffset();
			partShoeF.animRotation = bones.legsF.angle;

			partShoeB.animOffset   = bones.legsB.getEndOffset();
			partShoeB.animRotation = bones.legsB.angle;
			break;
	}
}



/***********************************************************************
     * ModelHumanoid
     * processArmsAnimation

***********************************************************************/
void fired::ModelHumanoid::processArmsAnimation() {
	switch (armsAnimation) {
		case caNone:
		case caJumping:
		case caMoving:
			armsAnimationTime = 0.0f;
			switch (bodyAnimation) {
				case caNone:
				case caShooting:
				case caMeleeAttack:
				case caBroadAttack:
					partWeapon.animRotation = 90;
					break;

				case caJumping:
					partWeapon.animOffset = sf::Vector2f(5.0, -4.0);

					partFistF.animRotation = -90.0;
					partFistB.animRotation = -90.0;

					partFistF.animOffset = sf::Vector2f(-3.0, -3.0);
					partFistB.animOffset = sf::Vector2f(-3.0, -3.0);

					if (owner->weapon->type == WEAPON_TYPE_BROAD) partWeapon.animRotation = -90;
					break;

				case caMoving:
					partArms.animRotation = -cos(0.449 * (bodyFrame - 7)) * 7.0;
					partWeapon.animOffset = sf::Vector2f(5.0 + cos(0.449 * (bodyFrame - 7)), -4.0);

					partFistF.animOffset = sf::Vector2f(-3.0 + cos(0.449 * (bodyFrame - 7)), -3.0);
					partFistB.animOffset = sf::Vector2f(-3.0 - cos(0.449 * (bodyFrame - 7)), -3.0);

					partFistF.animRotation = -90.0;
					partFistB.animRotation = -90.0;

					if (owner->weapon->type == WEAPON_TYPE_BROAD) partWeapon.animRotation = -90;
					break;
			}
			break;


		case caShooting:
			armsAnimationTime = 0.0f;

			partArms.animRotation = -90 + owner->aiming * 180 / 3.14;
			if (*partArms.direction < 0) partArms.animRotation = -partArms.animRotation;

			partFistF.animRotation = partArms.animRotation;
			partFistF.animOffset = sf::Vector2f(0.0, -8.0) + sf::Vector2f(8.0 * cos(owner->aiming), 8.0 * sin(owner->aiming));
			partFistB.animOffset = sf::Vector2f(-5.0, 0.0);

			if (*partFistF.direction < 0) {
				partFistF.animOffset.x = -partFistF.animOffset.x;
			}

			partWeapon.animOffset = sf::Vector2f(0.0, -12.0) + sf::Vector2f(12.0 * cos(owner->aiming), 12.0 * sin(owner->aiming));
			partWeapon.animRotation = owner->aiming * 180 / 3.14;

			if (*partWeapon.direction < 0) {
				partWeapon.animRotation = 180 - partWeapon.animRotation;
				partWeapon.animOffset.x = -partWeapon.animOffset.x;
			}
			break;


		case caMeleeAttack:
			if (armsAnimationTime < 0.2) {
				armsAnimationTime += frameClock;

				partArms.animRotation = -90 + owner->aiming * 180 / 3.14;
				if (*partArms.direction < 0) partArms.animRotation = -partArms.animRotation;

				partFistF.animRotation = partArms.animRotation;
				partFistF.animOffset = sf::Vector2f(0.0, -8.0) + sf::Vector2f(8.0 * cos(owner->aiming), 8.0 * sin(owner->aiming));
				partFistB.animOffset = sf::Vector2f(-5.0, 0.0);

				if (*partFistF.direction < 0) {
					partFistF.animOffset.x = -partFistF.animOffset.x;
				}

				partWeapon.animOffset = sf::Vector2f(0.0, -12.0) + sf::Vector2f(12.0 * cos(owner->aiming), 12.0 * sin(owner->aiming));
				partWeapon.animRotation = owner->aiming * 180 / 3.14;

				if (*partWeapon.direction < 0) {
					partWeapon.animRotation = 180 - partWeapon.animRotation;
					partWeapon.animOffset.x = -partWeapon.animOffset.x;
				}
			} else armsAnimation = caNone;
			break;


		case caBroadAttack:
			if (armsAnimationTime < BROAD_ATTACK_TIME) {
				armsAnimationTime += frameClock;

				partArms.animRotation = (armsAnimationTime / BROAD_ATTACK_TIME - 1.0f) * 180;

				partFistF.animRotation = partArms.animRotation;
				partFistF.animOffset = sf::Vector2f(0.0, -8.0) + sf::Vector2f(8.0 * cos(3.14 * (armsAnimationTime / BROAD_ATTACK_TIME - 1.0f) + 1.57), 8.0 * sin(3.14 * (armsAnimationTime / BROAD_ATTACK_TIME - 1.0f) + 1.57));
				partFistB.animOffset = sf::Vector2f(-5.0, 0.0);

				partWeapon.animOffset = sf::Vector2f(0.0, -12.0) + sf::Vector2f(12.0 * cos(3.14 * (armsAnimationTime / BROAD_ATTACK_TIME - 1.0f) + 1.57), 12.0 * sin(3.14 * (armsAnimationTime / BROAD_ATTACK_TIME - 1.0f) + 1.57));
				partWeapon.animRotation = partArms.animRotation + 90;
			} else armsAnimation = caNone;
			break;
	}
}
