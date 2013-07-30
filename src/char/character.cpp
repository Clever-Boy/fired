#include "game.hpp"


void fired::Character::init(fired::Game *_game) {
	game     = _game;
	settings = game->getSettings();
	app      = game->getApp();

	phys.pos          = sf::Vector2f(384, 2360);
	phys.velocity     = sf::Vector2f(0, 0);
	phys.acceleration = sf::Vector2f(0, PHYS_GRAVITY);
	phys.size         = sf::Vector2f(32, 48);
	phys.rect         = sf::FloatRect(phys.pos, phys.size);
	phys.onGround     = false;

	baseStats.speed  = 180.0;
	baseStats.accel  = 1200.0;
	baseStats.jump   = 520.0;
	baseStats.aiming = 100.0;

	model.init(game, this);
	isMoving  = false;
	direction = 1;
	watching  = 1;
}



void fired::Character::deinit() {
	model.deinit();
}



void fired::Character::update() {
	if (isMoving) {
		phys.velocity.x += direction * frameClock * baseStats.accel;
		if (abs(phys.velocity.x) > baseStats.speed) phys.velocity.x = direction * baseStats.speed;
	} else
		phys.velocity.x = 0;

	model.update();
	isMoving = false;
}



void fired::Character::moveLeft() {
	direction = -1;
	isMoving  = true;
}



void fired::Character::moveRight() {
	direction = 1;
	isMoving  = true;
}



void fired::Character::jump() {
	if (phys.onGround) phys.velocity.y = -baseStats.jump;
}
