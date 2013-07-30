#include "game.hpp"


void fired::Model::init(fired::Game *_game, fired::Character *_owner) {
	game     = _game;
	settings = game->getSettings();
	app      = game->getApp();
	owner    = _owner;


	initPart(&partLegsF, sf::Vector2f( 8, 36), "data/img/chars/legs.tga", &owner->direction);
	initPart(&partLegsB, sf::Vector2f(13, 36), "data/img/chars/legs.tga", &owner->direction);
	initPart(&partShoeF, sf::Vector2f( 8, 43), "data/img/chars/shoe.tga", &owner->direction);
	initPart(&partShoeB, sf::Vector2f(13, 43), "data/img/chars/shoe.tga", &owner->direction);
	initPart(&partFistF, sf::Vector2f( 2, 30), "data/img/chars/fist.tga", &owner->watching);
	initPart(&partFistB, sf::Vector2f(16, 30), "data/img/chars/fist.tga", &owner->watching);
	initPart(&partBody , sf::Vector2f( 5, 18), "data/img/chars/body.tga", &owner->watching);
	initPart(&partHead , sf::Vector2f(10, 9 ), "data/img/chars/head.tga", &owner->watching);
	initPart(&partHair , sf::Vector2f( 8, 4 ), "data/img/chars/hair.tga", &owner->watching);
	initPart(&partArms , sf::Vector2f( 3, 18), "data/img/chars/arms.tga", &owner->watching);

	bodyParts.push_back(&partFistB);
	bodyParts.push_back(&partBody );
	bodyParts.push_back(&partHead );
	bodyParts.push_back(&partHair );
	bodyParts.push_back(&partLegsB);
	bodyParts.push_back(&partShoeB);
	bodyParts.push_back(&partLegsF);
	bodyParts.push_back(&partShoeF);
	bodyParts.push_back(&partArms );
	bodyParts.push_back(&partFistF);


	bodyAnimation = caNone;
	armsAnimation = caNone;

	bodyFrame = 0;
	armsFrame = 0;
}



void fired::Model::deinit() {
	for (int i = 0; i < bodyParts.size(); i++) deinitPart(bodyParts[i]);
	bodyParts.clear();
}



void fired::Model::update() {
	bodyAnimation = caNone;
	if (!owner->phys.onGround) bodyAnimation = caJumping;
	processAnimation();
	render();
}



void fired::Model::render() {
	for (int i = 0; i < bodyParts.size(); i++) drawPart(bodyParts[i]);
}



void fired::Model::initPart(fired::Bodypart *part, sf::Vector2f offset, const char *imgFile, int *direction) {
	part->texture      = new sf::Texture();
	part->sprite       = new sf::Sprite();
	part->offset       = offset;
	part->direction    = direction;
	part->animOffset   = sf::Vector2f(0, 0);
	part->animRotation = 0;

	part->texture->loadFromFile(imgFile);
	part->sprite->setTexture(*part->texture);
	part->texture->setSmooth(true);
}



void fired::Model::drawPart(fired::Bodypart *part) {
	part->sprite->setScale(*part->direction, 1);
	part->sprite->setRotation(*part->direction * part->animRotation);

	if (*part->direction == 1)
		part->sprite->setPosition(owner->phys.pos + part->offset + part->animOffset);
	else
		part->sprite->setPosition(owner->phys.pos + sf::Vector2f(-part->offset.x, part->offset.y)  + sf::Vector2f(-part->animOffset.x, part->animOffset.y) + sf::Vector2f(owner->phys.size.x, 0));

	app->draw(*part->sprite);
}



void fired::Model::deinitPart(fired::Bodypart *part) {
	delete part->sprite;
	delete part->texture;
}



void fired::Model::resetPart(fired::Bodypart *part) {
	part->animOffset   = sf::Vector2f(0, 0);
	part->animRotation = 0;;
}



void fired::Model::resetAnimation() {
	bodyFrame = 0;
	for (int i = 0; i < bodyParts.size(); i++) resetPart(bodyParts[i]);
}



void fired::Model::processAnimation() {
	processBodyAnimation();
	processArmsAnimation();
}



void fired::Model::processBodyAnimation() {
	switch (bodyAnimation) {
		case caNone:
			resetAnimation();
			break;

		case caJumping:
			resetAnimation();

			partLegsF.animRotation =  20;
			partLegsB.animRotation = -20;

			partLegsF.animOffset = sf::Vector2f(0, -2);
			partLegsB.animOffset = sf::Vector2f(0,  2);

			partShoeF.animOffset = sf::Vector2f(-3, -2);
			partShoeB.animOffset = sf::Vector2f( 3, -2);
			break;
	}
}



void fired::Model::processArmsAnimation() {
	switch (armsAnimation) {
		case caNone:
			switch (bodyAnimation) {
				case caJumping:
					partFistF.animOffset = sf::Vector2f(5, 3);
					partFistB.animOffset = sf::Vector2f(5, 3);

					partFistF.animRotation = -90;
					partFistB.animRotation = -90;
					break;
			}
			break;
	}
}
