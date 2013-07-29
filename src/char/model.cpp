#include "game.hpp"


void fired::Model::init(fired::Game *_game, fired::Character *_owner) {
	game     = _game;
	settings = game->getSettings();
	app      = game->getApp();
	owner    = _owner;

	texture = new sf::Texture();
	sprite  = new sf::Sprite();

	texture->loadFromFile("data/img/chars/player.tga");
	sprite->setTexture(*texture);
	texture->setSmooth(true);
}



void fired::Model::deinit() {
	delete sprite;
	delete texture;
}



void fired::Model::update() {
	render();
}



void fired::Model::render() {
	sprite->setPosition(owner->phys.pos);
	game->getApp()->draw(*sprite);
}
