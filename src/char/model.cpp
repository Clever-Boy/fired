#include "game.hpp"

//======================================================================


void fired::Model::init(fired::Game *_game, fired::Character *_owner, fired::BaseModel *base) {
	game     = _game;
	settings = game->getSettings();
	app      = game->getApp();
	owner    = _owner;


	initPart(&partLegsF , sf::Vector2f( 8, 36), "data/img/world/models/legsF/common.tga", &owner->direction);
	initPart(&partLegsB , sf::Vector2f(13, 36), "data/img/world/models/legsB/common.tga", &owner->direction);
	initPart(&partShoeF , sf::Vector2f( 8, 43), "data/img/world/models/shoeF/common.tga", &owner->direction);
	initPart(&partShoeB , sf::Vector2f(13, 43), "data/img/world/models/shoeB/common.tga", &owner->direction);
	initPart(&partFistF , sf::Vector2f( 2, 30), "data/img/world/models/fistF/common.tga", &owner->watching);
	initPart(&partFistB , sf::Vector2f(16, 30), "data/img/world/models/fistB/common.tga", &owner->watching);
	initPart(&partBody  , sf::Vector2f( 5, 18), "data/img/world/models/body/common.tga", &owner->watching);
	initPart(&partHead  , sf::Vector2f(10, 9 ), "data/img/world/models/head/common.tga", &owner->watching);
	initPart(&partHair  , sf::Vector2f( 8, 4 ), "data/img/world/models/hair/common.tga", &owner->watching);
	initPart(&partArms  , sf::Vector2f( 3, 18), "data/img/world/models/arms/common.tga", &owner->watching);
	initPart(&partWeapon, sf::Vector2f( 4, 29), "data/img/world/models/weapon/amp.tga", &owner->watching);

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


void fired::Model::deinit() {
	for (int i = 0; i < bodyParts.size(); i++) deinitPart(bodyParts[i]);
	bodyParts.clear();
}

//======================================================================


void fired::Model::update() {
	bodyAnimation = caNone;
	armsAnimation = caNone;

	if (owner->phys.isMoving)  bodyAnimation = caMoving;
	if (!owner->phys.onGround) bodyAnimation = caJumping;
	if (owner->isShooting)     armsAnimation = caShooting;

	processAnimation();
}

//======================================================================


void fired::Model::render() {
	for (int i = 0; i < bodyParts.size(); i++) drawPart(bodyParts[i]);
}

//======================================================================


void fired::Model::initPart(fired::Bodypart *part, sf::Vector2f offset, const char *imgFile, int *direction) {
	part->texture      = new sf::Texture();
	part->sprite       = new sf::Sprite();
	part->offset       = offset;
	part->direction    = direction;
	part->animOffset   = sf::Vector2f(0.0, 0.0);
	part->animRotation = 0.0;

	part->texture->loadFromFile(imgFile);
	part->sprite->setTexture(*part->texture);
	part->texture->setSmooth(true);
}

//======================================================================


void fired::Model::drawPart(fired::Bodypart *part) {
	part->sprite->setScale(*part->direction, 1.0);
	part->sprite->setRotation(*part->direction * part->animRotation);

	if (*part->direction == 1)
		part->sprite->setPosition(owner->phys.pos + part->offset + part->animOffset);
	else
		part->sprite->setPosition(owner->phys.pos + sf::Vector2f(-part->offset.x, part->offset.y) + sf::Vector2f(-part->animOffset.x, part->animOffset.y) + sf::Vector2f(owner->phys.size.x, 0));

	app->draw(*part->sprite);
}

//======================================================================


void fired::Model::deinitPart(fired::Bodypart *part) {
	delete part->sprite;
	delete part->texture;
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

//======================================================================


void fired::Model::processAnimation() {
	resetAnimation();
	processBodyAnimation();
	processArmsAnimation();
}

//======================================================================


void fired::Model::processBodyAnimation() {
	switch (bodyAnimation) {
		case caNone:
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


void fired::Model::processArmsAnimation() {
	switch (armsAnimation) {
		case caNone:
			switch (bodyAnimation) {
				case caNone:
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
			partWeapon.animOffset = sf::Vector2f(5.0 + 4.0 * cos(owner->aiming - 1.54), -4.0);
			partWeapon.animRotation = owner->aiming * 180 / 3.14;
			if (*partWeapon.direction < 0) partWeapon.animRotation = 180 - partWeapon.animRotation;

			partFistF.animOffset = sf::Vector2f(5.0, 3.0);
			partFistF.animRotation = -90.0;

			partFistB.animOffset = sf::Vector2f(-5.0, 0.0);
			break;
	}
}
