#include "game.hpp"


void fired::Character::init(fired::Game *_game) {
	game     = _game;
	settings = game->getSettings();
	app      = game->getApp();

	phys.pos          = sf::Vector2f(384, 0);
	phys.velocity     = sf::Vector2f(0, 0);
	phys.acceleration = sf::Vector2f(0, PHYS_GRAVITY);
	phys.size         = sf::Vector2f(32, 48);

	baseStats.speed = 120.0;
	baseStats.accel = 1200.0;

	isMoving  = false;
	direction = 1;

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
	if (isMoving) {
		phys.velocity.x += direction * frameClock * baseStats.accel;
		if (abs(phys.velocity.x) > baseStats.speed) phys.velocity.x = direction * baseStats.speed;
	} else
		phys.velocity.x = 0;

	isMoving = false;
	render();
}



void fired::Character::render() {
	sprite->setPosition(phys.pos);
	game->getApp()->draw(*sprite);
}



void fired::Character::moveLeft() {
	direction = -1;
	isMoving  = true;
}


void fired::Character::moveRight() {
	direction = 1;
	isMoving  = true;
}
