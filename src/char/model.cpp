#include "game.hpp"


void fired::Model::init(fired::Game *_game, fired::Character *_owner) {
	game     = _game;
	settings = game->getSettings();
	app      = game->getApp();
	owner    = _owner;

	offsetHair  = sf::Vector2f(11, 4 );
	offsetHead  = sf::Vector2f(13, 9 );
	offsetBody  = sf::Vector2f(8 , 18);
	offsetArms  = sf::Vector2f(6 , 18);
	offsetLegsB = sf::Vector2f(16, 36);
	offsetLegsF = sf::Vector2f(11, 36);
	offsetFistB = sf::Vector2f(19, 30);
	offsetFistF = sf::Vector2f(5 , 30);
	offsetShoeB = sf::Vector2f(16, 43);
	offsetShoeF = sf::Vector2f(11, 43);

	initPart(&spriteArms, &textureArms, "data/img/chars/arms.tga");
	initPart(&spriteFist, &textureFist, "data/img/chars/fist.tga");
	initPart(&spriteShoe, &textureShoe, "data/img/chars/shoe.tga");
	initPart(&spriteHair, &textureHair, "data/img/chars/hair.tga");
	initPart(&spriteHead, &textureHead, "data/img/chars/head.tga");
	initPart(&spriteBody, &textureBody, "data/img/chars/body.tga");
	initPart(&spriteLegs, &textureLegs, "data/img/chars/legs.tga");
}



void fired::Model::deinit() {
	delete spriteHair;
	delete spriteHead;
	delete spriteBody;
	delete spriteLegs;
	delete spriteArms;
	delete spriteShoe;
	delete spriteFist;

	delete textureHair;
	delete textureHead;
	delete textureBody;
	delete textureLegs;
	delete textureArms;
	delete textureShoe;
	delete textureFist;
}



void fired::Model::update() {
	spriteArms->setScale(owner->direction, 1);
	spriteHead->setScale(owner->direction, 1);
	spriteHair->setScale(owner->direction, 1);
	spriteBody->setScale(owner->direction, 1);
	spriteLegs->setScale(owner->direction, 1);
	spriteFist->setScale(owner->direction, 1);
	spriteShoe->setScale(owner->direction, 1);

	render();
}



void fired::Model::render() {
	drawPart(spriteFist, offsetFistB);
	drawPart(spriteBody, offsetBody );
	drawPart(spriteHead, offsetHead );
	drawPart(spriteHair, offsetHair );
	drawPart(spriteLegs, offsetLegsB);
	drawPart(spriteShoe, offsetShoeB);
	drawPart(spriteLegs, offsetLegsF);
	drawPart(spriteShoe, offsetShoeF);
	drawPart(spriteArms, offsetArms );
	drawPart(spriteFist, offsetFistF);
}



void fired::Model::initPart(sf::Sprite **spr, sf::Texture **tex, const char *imgFile) {
	*tex = new sf::Texture();
	*spr = new sf::Sprite();

	(*tex)->loadFromFile(imgFile);
	(*spr)->setTexture(**tex);
	(*tex)->setSmooth(true);
}



void fired::Model::drawPart(sf::Sprite *spr, sf::Vector2f offset) {
	if (owner->direction == 1) 
		spr->setPosition(owner->phys.pos + offset);
	else
		spr->setPosition(owner->phys.pos + sf::Vector2f(-offset.x, offset.y) + sf::Vector2f(owner->phys.size.x, 0));

	app->draw(*spr);
}
