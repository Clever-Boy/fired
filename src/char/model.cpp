#include "game.hpp"


void initPart(sf::Sprite **spr, sf::Texture **tex, const char *imgFile) {
	*tex = new sf::Texture();
	*spr = new sf::Sprite();

	(*tex)->loadFromFile(imgFile);
	(*spr)->setTexture(**tex);
	(*tex)->setSmooth(true);
}



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

	delete textureHair;
	delete textureHead;
	delete textureBody;
	delete textureLegs;
	delete textureArms;
}



void fired::Model::update() {
	render();
}



void fired::Model::render() {
	//Back fist
	spriteFist->setPosition(owner->phys.pos + offsetFistB);
	game->getApp()->draw(*spriteFist);

	//Body
	spriteBody->setPosition(owner->phys.pos + offsetBody);
	game->getApp()->draw(*spriteBody);

	//Head
	spriteHead->setPosition(owner->phys.pos + offsetHead);
	game->getApp()->draw(*spriteHead);

	//Hair
	spriteHair->setPosition(owner->phys.pos + offsetHair);
	game->getApp()->draw(*spriteHair);

	//Back leg
	spriteLegs->setPosition(owner->phys.pos + offsetLegsB);
	game->getApp()->draw(*spriteLegs);

	//Back shoe
	spriteShoe->setPosition(owner->phys.pos + offsetShoeB);
	game->getApp()->draw(*spriteShoe);

	//Front leg
	spriteLegs->setPosition(owner->phys.pos + offsetLegsF);
	game->getApp()->draw(*spriteLegs);

	//Front shoe
	spriteShoe->setPosition(owner->phys.pos + offsetShoeF);
	game->getApp()->draw(*spriteShoe);

	//Arm
	spriteArms->setPosition(owner->phys.pos + offsetArms);
	game->getApp()->draw(*spriteArms);

	//Front fist
	spriteFist->setPosition(owner->phys.pos + offsetFistF);
	game->getApp()->draw(*spriteFist);
}
