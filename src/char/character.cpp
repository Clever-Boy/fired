#include "game.hpp"


void fired::Character::init(fired::Game *_game) {
	game     = _game;
	settings = game->getSettings();
	app      = game->getApp();

	pos          = sf::Vector2f(384, 0);
	velocity     = sf::Vector2f(0, 0);
	acceleration = sf::Vector2f(0, PHYS_GRAVITY);
	size         = sf::Vector2f(32, 48);

	baseStats.speed = 120.0;

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



void fired::Character::update() {
	velocity.x = 0;
	velocity += acceleration;
	if (velocity.x > PHYS_MAX_FALL) velocity.x = PHYS_MAX_FALL;
	if (velocity.y > PHYS_MAX_FALL) velocity.y = PHYS_MAX_FALL;

	pos += velocity;

	render();
}



void fired::Character::render() {
	sprite->setPosition(pos);
	game->getApp()->draw(*sprite);
}



void fired::Character::moveLeft() {
	velocity.x = -frameClock * baseStats.speed;
}


void fired::Character::moveRight() {
	velocity.x = frameClock * baseStats.speed;
}
