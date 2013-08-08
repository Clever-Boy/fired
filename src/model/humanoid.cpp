#include "game.hpp"

//======================================================================


void fired::ModelHumanoid::init(fired::Game *_game, fired::Character *_owner, fired::BaseModelHumanoid *base, float scale, fired::World *_world) {
	game     = _game;
	settings = game->getSettings();
	app      = game->getApp();
	owner    = _owner;
	world    = _world;

	modelScale = scale;
	owner->phys.size       = base->size * scale;
	owner->phys.headSize   = sf::Vector2f(owner->phys.size.x, owner->phys.size.y / 3);
	owner->phys.headOffset = sf::Vector2f(0, 0);
	owner->phys.calculate();


	initPart(&partLegsF , base->partLegsF, &owner->direction);
	initPart(&partLegsB , base->partLegsB, &owner->direction);
	initPart(&partShoeF , base->partShoeF, &owner->direction);
	initPart(&partShoeB , base->partShoeB, &owner->direction);
	initPart(&partFistF , base->partFistF, &owner->watching);
	initPart(&partFistB , base->partFistB, &owner->watching);
	initPart(&partBody  , base->partBody, &owner->watching);
	initPart(&partHead  , base->partHead, &owner->watching);
	initPart(&partHair  , base->partHair, &owner->watching);
	initPart(&partArms  , base->partArms, &owner->watching);
	initPart(&partWeapon, base->partWeapon, &owner->watching);

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


void fired::ModelHumanoid::update() {
	if (owner->isDead()) {
		if (bodyAnimation != caDying) {
			bodyAnimationTime = 0.0;
			armsAnimationTime = 0.0;

			bodyAnimation = caDying;
			armsAnimation = caDying;
		}
	} else {
		bodyAnimation = caNone;
		armsAnimation = caNone;

		if (owner->phys.isMoving)  bodyAnimation = caMoving;
		if (!owner->phys.onGround) bodyAnimation = caJumping;
		if (owner->isShooting)     armsAnimation = caShooting;
	}

	processAnimation();
}

//======================================================================


void fired::ModelHumanoid::headshot() {
	bodyParts.erase(bodyParts.begin() + 4);
	bodyParts.erase(bodyParts.begin() + 4);
	world->addBloodSplash(owner->phys.pos + owner->phys.headOffset + owner->phys.headSize / 2.0f, sf::Vector2f(0.0f, -400.0f), 50);
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


		case caDying:
			bodyAnimationTime += frameClock;
			bodyFrame          = (int)(bodyAnimationTime * 100);

			if (bodyFrame < 18) {
				partShoeF.animRotation = 5 * bodyFrame;
				partShoeB.animRotation = 5 * bodyFrame;

				partLegsF.animRotation = 5 * bodyFrame;
				partLegsB.animRotation = 5 * bodyFrame;
				partLegsF.animOffset   = sf::Vector2f(partLegsF.base->size.y * sin(partLegsF.animRotation * 3.14 / 180.0), partLegsF.base->size.y * (bodyFrame / 18.0));
				partLegsB.animOffset   = sf::Vector2f(partLegsF.base->size.y * sin(partLegsF.animRotation * 3.14 / 180.0), partLegsF.base->size.y * (bodyFrame / 18.0));

				partBody.animOffset = sf::Vector2f(partLegsF.base->size.y * sin(partLegsF.animRotation * 3.14 / 180.0), (partLegsF.base->size.y + partLegsF.base->size.x / 2) * bodyFrame / 18);
				partHead.animOffset = sf::Vector2f(partLegsF.base->size.y * sin(partLegsF.animRotation * 3.14 / 180.0), (partLegsF.base->size.y + partLegsF.base->size.x / 2) * bodyFrame / 18);
				partHair.animOffset = sf::Vector2f(partLegsF.base->size.y * sin(partLegsF.animRotation * 3.14 / 180.0), (partLegsF.base->size.y + partLegsF.base->size.x / 2) * bodyFrame / 18);
				partArms.animOffset = sf::Vector2f(partLegsF.base->size.y * sin(partLegsF.animRotation * 3.14 / 180.0), (partLegsF.base->size.y + partLegsF.base->size.x / 2) * bodyFrame / 18);
				partFistF.animOffset = sf::Vector2f(partLegsF.base->size.y * sin(partLegsF.animRotation * 3.14 / 180.0), (partLegsF.base->size.y + partLegsF.base->size.x / 2) * bodyFrame / 18);
				partFistB.animOffset = sf::Vector2f(partLegsF.base->size.y * sin(partLegsF.animRotation * 3.14 / 180.0), (partLegsF.base->size.y + partLegsF.base->size.x / 2) * bodyFrame / 18);
				partWeapon.animOffset = sf::Vector2f(partLegsF.base->size.y * sin(partLegsF.animRotation * 3.14 / 180.0), (partLegsF.base->size.y + partLegsF.base->size.x / 2) * bodyFrame / 18);
			} else /*if (bodyFrame < 18)*/ {
				partShoeF.animRotation = 90;
				partShoeB.animRotation = 90;

				partLegsF.animRotation = 90;
				partLegsB.animRotation = 90;
				partLegsF.animOffset   = sf::Vector2f(partLegsF.base->size.y, partLegsF.base->size.y);
				partLegsB.animOffset   = sf::Vector2f(partLegsF.base->size.y, partLegsF.base->size.y);


				partBody.animOffset = sf::Vector2f(partLegsF.base->size.y, (partLegsF.base->size.y + partLegsF.base->size.x / 2));
				partHead.animOffset = sf::Vector2f(partLegsF.base->size.y, (partLegsF.base->size.y + partLegsF.base->size.x / 2));
				partHair.animOffset = sf::Vector2f(partLegsF.base->size.y, (partLegsF.base->size.y + partLegsF.base->size.x / 2));
				partArms.animOffset = sf::Vector2f(partLegsF.base->size.y, (partLegsF.base->size.y + partLegsF.base->size.x / 2));
				partFistF.animOffset = sf::Vector2f(partLegsF.base->size.y, (partLegsF.base->size.y + partLegsF.base->size.x / 2));
				partFistB.animOffset = sf::Vector2f(partLegsF.base->size.y, (partLegsF.base->size.y + partLegsF.base->size.x / 2));
				partWeapon.animOffset = sf::Vector2f(partLegsF.base->size.y, (partLegsF.base->size.y + partLegsF.base->size.x / 2));
/*
			} else if (bodyFrame < 27) {
				partLegsF.animRotation = 90;
				partLegsB.animRotation = 90;
				partLegsF.animOffset   = sf::Vector2f(10.0, 3.0);
				partLegsB.animOffset   = sf::Vector2f(10.0, 3.0);

				partShoeF.animRotation = 90;
				partShoeB.animRotation = 90;
				partShoeF.animOffset   = sf::Vector2f(0.0, -4.0);
				partShoeB.animOffset   = sf::Vector2f(0.0, -4.0);

				partBody.animOffset = sf::Vector2f(10.0, 10.0);
				partHead.animOffset = sf::Vector2f(10.0, 10.0);
				partHair.animOffset = sf::Vector2f(10.0, 10.0);
				partArms.animOffset = sf::Vector2f(10.0, 10.0);
				partFistF.animOffset = sf::Vector2f(10.0, 10.0);
				partFistB.animOffset = sf::Vector2f(10.0, 10.0);
				partWeapon.animOffset = sf::Vector2f(10.0, 10.0);

				partBody.animRotation = 10 * (bodyFrame - 18);
				partHead.animRotation = 10 * (bodyFrame - 18);
				partHair.animRotation = 10 * (bodyFrame - 18);
				partArms.animRotation = 10 * (bodyFrame - 18);
				partFistF.animRotation = 10 * (bodyFrame - 18);
				partFistB.animRotation = 10 * (bodyFrame - 18);
				partWeapon.animRotation = 10 * (bodyFrame - 18);
			} else {
				partLegsF.animRotation = 90;
				partLegsB.animRotation = 90;
				partLegsF.animOffset   = sf::Vector2f(10.0, 3.0);
				partLegsB.animOffset   = sf::Vector2f(10.0, 3.0);

				partShoeF.animRotation = 90;
				partShoeB.animRotation = 90;
				partShoeF.animOffset   = sf::Vector2f(0.0, -4.0);
				partShoeB.animOffset   = sf::Vector2f(0.0, -4.0);

				partBody.animOffset = sf::Vector2f(10.0, 10.0);
				partHead.animOffset = sf::Vector2f(10.0, 10.0);
				partHair.animOffset = sf::Vector2f(10.0, 10.0);
				partArms.animOffset = sf::Vector2f(10.0, 10.0);
				partFistF.animOffset = sf::Vector2f(10.0, 10.0);
				partFistB.animOffset = sf::Vector2f(10.0, 10.0);
				partWeapon.animOffset = sf::Vector2f(10.0, 10.0);

				partBody.animRotation = 90;
				partHead.animRotation = 90;
				partHair.animRotation = 90;
				partArms.animRotation = 90;
				partFistF.animRotation = 90;
				partFistB.animRotation = 90;
				partWeapon.animRotation = 90;
*/
			}

			break;
	}
}

//======================================================================


void fired::ModelHumanoid::processArmsAnimation() {
	switch (armsAnimation) {
		case caNone:
		case caJumping:
		case caMoving:
			switch (bodyAnimation) {
				case caNone:
				case caShooting:
					partWeapon.animOffset = sf::Vector2f(7, 0);
					partWeapon.animRotation = 90;
					break;

				case caJumping:
					partWeapon.animOffset = sf::Vector2f(5.0, -4.0);

					partFistF.animOffset = sf::Vector2f(5.0, 3.0);
					partFistB.animOffset = sf::Vector2f(5.0, 3.0);

					partFistF.animRotation = -90.0;
					partFistB.animRotation = -90.0;
					break;

				case caMoving:
					partArms.animRotation = -cos(0.449 * (bodyFrame - 7)) * 7.0;

					partWeapon.animOffset = sf::Vector2f(5.0 + cos(0.449 * (bodyFrame - 7)), -4.0);

					partFistF.animOffset = sf::Vector2f(5.0 + cos(0.449 * (bodyFrame - 7)), 4.0);
					partFistB.animOffset = sf::Vector2f(5.0 - cos(0.449 * (bodyFrame - 7)), 4.0);

					partFistF.animRotation = -90.0;
					partFistB.animRotation = -90.0;
					break;

				case caDying:
					break;
			}
			break;


		case caShooting:
			partWeapon.animOffset = sf::Vector2f(5.0 + 4.0 * cos(owner->aiming - 1.54), -4.0);
			partWeapon.animRotation = owner->aiming * 180 / 3.14;
			if (*partWeapon.direction < 0) partWeapon.animRotation = 180 - partWeapon.animRotation;

			partFistF.animOffset = sf::Vector2f(5.0, 3.0);
			partFistF.animRotation = -90.0;

			partFistB.animOffset = sf::Vector2f(-5.0, 0.0);
			break;


		case caDying:
			break;
	}
}
