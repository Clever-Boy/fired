#include "game.hpp"

//======================================================================


fired::ModelHumanoid::ModelHumanoid(fired::Game *_game, fired::Character *_owner, fired::BaseModelHumanoid *base, float scale, fired::World *_world) {
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

	respawn();
}

//======================================================================


void fired::ModelHumanoid::update() {
	if (owner->isDead()) {
		if (bodyAnimation != caNone) {
			bodyAnimation = caNone;
			armsAnimation = caNone;
		}
	} else {
		bodyAnimation = caNone;
		armsAnimation = caNone;

		if (owner->phys.isMoving)  bodyAnimation = caMoving;
		if (!owner->phys.onGround) bodyAnimation = caJumping;
		if (owner->isShooting)     armsAnimation = caShooting;
		if (owner->isReloading)    armsAnimation = caReloading;
	}

	processAnimation();
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
		case caReloading:
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
			}
			break;


		case caShooting:
			armsAnimationTime = 0.0f;

			partWeapon.animOffset = sf::Vector2f(5.0 + 4.0 * cos(owner->aiming - 1.54), -4.0);
			partWeapon.animRotation = owner->aiming * 180 / 3.14;
			if (*partWeapon.direction < 0) partWeapon.animRotation = 180 - partWeapon.animRotation;

			partFistF.animOffset = sf::Vector2f(5.0, 3.0);
			partFistF.animRotation = -90.0;

			partFistB.animOffset = sf::Vector2f(-5.0, 0.0);
			break;


		case caReloading:
			armsAnimationTime += frameClock;

			partArms.animRotation = -cos(0.449 * (bodyFrame - 7)) * 7.0;
			partWeapon.animOffset = sf::Vector2f(5.0 + cos(0.449 * (bodyFrame - 7)), -4.0);

			partFistF.animOffset = sf::Vector2f(5.0 + cos(0.449 * (bodyFrame - 7)), 4.0);
			partFistB.animOffset = sf::Vector2f(5.0 - cos(0.449 * (bodyFrame - 7)), 4.0 + 5.0 * sin(3.14 * (owner->weapon->reload - armsAnimationTime) / owner->weapon->reload));

			partFistF.animRotation = -90.0;
			partFistB.animRotation = -90.0;
			break;
	}
}
