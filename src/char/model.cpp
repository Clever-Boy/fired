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

	initPart(&spriteArms, &textureArms, "data/img/chars/player.tga");
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
	spriteBody->setPosition(owner->phys.pos);
	game->getApp()->draw(*spriteBody);

	spriteHead->setPosition(owner->phys.pos);
	game->getApp()->draw(*spriteHead);

	spriteHair->setPosition(owner->phys.pos);
	game->getApp()->draw(*spriteHair);

	spriteLegs->setPosition(owner->phys.pos);
	spriteLegs->move(5, 0);
	game->getApp()->draw(*spriteLegs);
	spriteLegs->move(-5, 0);
	game->getApp()->draw(*spriteLegs);
}
