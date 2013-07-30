#include "game.hpp"


void fired::Model::init(fired::Game *_game, fired::Character *_owner) {
	game     = _game;
	settings = game->getSettings();
	app      = game->getApp();
	owner    = _owner;

	initPart(&partLegsF, sf::Vector2f(11, 36), "data/img/chars/legs.tga");
	initPart(&partLegsB, sf::Vector2f(16, 36), "data/img/chars/legs.tga");
	initPart(&partShoeF, sf::Vector2f(11, 43), "data/img/chars/shoe.tga");
	initPart(&partShoeB, sf::Vector2f(16, 43), "data/img/chars/shoe.tga");
	initPart(&partFistF, sf::Vector2f(5 , 30), "data/img/chars/fist.tga");
	initPart(&partFistB, sf::Vector2f(19, 30), "data/img/chars/fist.tga");
	initPart(&partBody , sf::Vector2f(8 , 18), "data/img/chars/body.tga");
	initPart(&partHead , sf::Vector2f(13, 9 ), "data/img/chars/head.tga");
	initPart(&partHair , sf::Vector2f(11, 4 ), "data/img/chars/hair.tga");
	initPart(&partArms , sf::Vector2f(6 , 18), "data/img/chars/arms.tga");
}



void fired::Model::deinit() {
	deinitPart(&partLegsF);
	deinitPart(&partLegsB);
	deinitPart(&partShoeF);
	deinitPart(&partShoeB);
	deinitPart(&partFistF);
	deinitPart(&partFistB);
	deinitPart(&partHead );
	deinitPart(&partHair );
	deinitPart(&partBody );
	deinitPart(&partArms );
}



void fired::Model::update() {
	render();
}



void fired::Model::render() {
	drawPart(&partFistB);
	drawPart(&partBody );
	drawPart(&partHead );
	drawPart(&partHair );
	drawPart(&partLegsB);
	drawPart(&partShoeB);
	drawPart(&partLegsF);
	drawPart(&partShoeF);
	drawPart(&partArms );
	drawPart(&partFistF);
}



void fired::Model::initPart(fired::Bodypart *part, sf::Vector2f offset, const char *imgFile) {
	part->texture = new sf::Texture();
	part->sprite  = new sf::Sprite();
	part->offset  = offset;

	part->texture->loadFromFile(imgFile);
	part->sprite->setTexture(*part->texture);
	part->texture->setSmooth(true);
}



void fired::Model::drawPart(fired::Bodypart *part) {
	part->sprite->setScale(owner->direction, 1);
	if (owner->direction == 1)
		part->sprite->setPosition(owner->phys.pos + part->offset);
	else
		part->sprite->setPosition(owner->phys.pos + sf::Vector2f(-part->offset.x, part->offset.y) + sf::Vector2f(owner->phys.size.x, 0));

	app->draw(*part->sprite);
}



void fired::Model::deinitPart(fired::Bodypart *part) {
	delete part->sprite;
	delete part->texture;
}
