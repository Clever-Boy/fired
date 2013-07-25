#include "game.hpp"


void fired::Character::init(fired::Game *_game) {
	game = _game;
	pos  = sf::Vector2f(384, 432);
	size = sf::Vector2f(32, 48);

	texture = new sf::Texture();
	sprite  = new sf::Sprite();

	texture->loadFromFile("data/img/chars/player.tga");
	sprite->setTexture(*texture);
	texture->setSmooth(true);
}



void fired::Character::deinit() {
	delete sprite;
	delete texture;
}



void fired::Character::update(float frameClock) {
	render();
}



void fired::Character::render() {
	sprite->setPosition(pos);
	game->getApp()->draw(*sprite);
}
