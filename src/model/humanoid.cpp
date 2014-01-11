#include "game.hpp"

//======================================================================


fired::ModelHumanoid::ModelHumanoid(fired::Character *_owner, fired::BaseModelHumanoid *_base, float scale, fired::World *_world) {
	owner    = _owner;
	world    = _world;
	base     = _base;

	modelScale = scale;
	owner->phys.size       = base->size * scale;
	owner->phys.calculate();

	updateParts();
	respawn();
}

//======================================================================


void fired::ModelHumanoid::update() {
	if (owner->dead) {
		if (bodyAnimation != caNone) {
			bodyAnimation = caNone;
			armsAnimation = caNone;
		}
	} else {
		bodyAnimation = caNone;
		if (armsAnimation == caShooting || armsAnimation == caReloading) armsAnimation = caNone;

		if (owner->phys.isMoving)  bodyAnimation = caMoving;
		if (!owner->phys.onGround) bodyAnimation = caJumping;

		if (owner->isShooting) {
			if (owner->weapon->type == WEAPON_TYPE_RANGED) armsAnimation = caShooting;
			if (owner->weapon->type == WEAPON_TYPE_MELEE)  armsAnimation = caMeleeAttack;
			if (owner->weapon->type == WEAPON_TYPE_BROAD)  armsAnimation = caBroadAttack;
		}

		if (owner->isReloading)    armsAnimation = caReloading;
	}

	processAnimation();
}

//======================================================================


void fired::ModelHumanoid::updateParts() {
	initPart(&partHead, base->partHead.part, base->partHead.color, base->partHead.offset, &owner->watching);


	if (owner->helm) initPart(&partHair, world->getBodypart(owner->helm->model, bptHair), owner->helm->color  , base->partHair.offset, &owner->watching);
	else             initPart(&partHair, base->partHair.part                            , base->partHair.color, base->partHair.offset, &owner->watching);

	if (owner->body) initPart(&partBody, world->getBodypart(owner->body->model, bptBody), owner->body->color  , base->partBody.offset, &owner->watching);
	else             initPart(&partBody, base->partBody.part                            , base->partBody.color, base->partBody.offset, &owner->watching);

	if (owner->arms) initPart(&partArms, world->getBodypart(owner->arms->model, bptArms), owner->arms->color  , base->partArms.offset, &owner->watching);
	else             initPart(&partArms, base->partArms.part                            , base->partArms.color, base->partArms.offset, &owner->watching);


	if (owner->legs) {
		initPart(&partLegsF, world->getBodypart(owner->legs->model, bptLegsF), owner->legs->color   , base->partLegsF.offset, &owner->direction);
		initPart(&partLegsB, world->getBodypart(owner->legs->model, bptLegsB), owner->legs->color   , base->partLegsB.offset, &owner->direction);
	} else {
		initPart(&partLegsF, base->partLegsF.part                            , base->partLegsF.color, base->partLegsF.offset, &owner->direction);
		initPart(&partLegsB, base->partLegsB.part                            , base->partLegsB.color, base->partLegsB.offset, &owner->direction);
	}

	if (owner->shoe) {
		initPart(&partShoeF, world->getBodypart(owner->shoe->model, bptShoeF), owner->shoe->color   , base->partShoeF.offset, &owner->direction);
		initPart(&partShoeB, world->getBodypart(owner->shoe->model, bptShoeB), owner->shoe->color   , base->partShoeB.offset, &owner->direction);
	} else {
		initPart(&partShoeF, base->partShoeF.part                            , base->partShoeF.color, base->partShoeF.offset, &owner->direction);
		initPart(&partShoeB, base->partShoeB.part                            , base->partShoeB.color, base->partShoeB.offset, &owner->direction);
	}

	if (owner->fist) {
		initPart(&partFistF, world->getBodypart(owner->fist->model, bptFistF), owner->fist->color   , base->partFistF.offset, &owner->watching);
		initPart(&partFistB, world->getBodypart(owner->fist->model, bptFistB), owner->fist->color   , base->partFistB.offset, &owner->watching);
	} else {
		initPart(&partFistF, base->partFistF.part                            , base->partFistF.color, base->partFistF.offset, &owner->watching);
		initPart(&partFistB, base->partFistB.part                            , base->partFistB.color, base->partFistB.offset, &owner->watching);
	}
}

//======================================================================


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

//======================================================================


void fired::ModelHumanoid::setWeapon(fired::BaseWeapon *weapon) {
	initPart(&partWeapon, world->getBodypart(weapon->model, bptWeapon), sf::Color::White, base->weaponOffset, &owner->watching);
}

//======================================================================


void fired::ModelHumanoid::processAnimation() {
	resetAnimation();
	processBodyAnimation();
	processArmsAnimation();
}

//======================================================================


void fired::ModelHumanoid::processBodyAnimation() {
	switch (bodyAnimation) {
		case caNone:
		case caShooting:
		case caReloading:
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
			break;


		case caJumping:
			bodyAnimationTime = 0.0;

			partLegsF.animRotation =  20.0;
			partLegsB.animRotation = -20.0;

			partLegsF.animOffset = sf::Vector2f( 0.0, -2.0);
			partLegsB.animOffset = sf::Vector2f( 0.0,  2.0);

			partShoeF.animOffset = sf::Vector2f(-3.0, -2.0);
			partShoeB.animOffset = sf::Vector2f( 3.0, -2.0);
			break;
	}
}

//======================================================================


void fired::ModelHumanoid::processArmsAnimation() {
	switch (armsAnimation) {
		case caNone:
		case caJumping:
		case caMoving:
			armsAnimationTime = 0.0f;
			switch (bodyAnimation) {
				case caNone:
				case caShooting:
				case caReloading:
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


		case caReloading:
			armsAnimationTime += frameClock;

			partArms.animRotation = -cos(0.449 * (bodyFrame - 7)) * 7.0;
			partWeapon.animOffset = sf::Vector2f(5.0 + cos(0.449 * (bodyFrame - 7)), -4.0);

			partFistF.animOffset = sf::Vector2f(-3.0, -3.0);
			partFistB.animOffset = sf::Vector2f(-3.0, -3.0 + 5.0 * sin(3.14 * (owner->weapon->reload - armsAnimationTime) / owner->weapon->reload));

			partFistF.animRotation = -90.0;
			partFistB.animRotation = -90.0;
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
