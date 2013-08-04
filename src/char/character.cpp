#include "game.hpp"

//======================================================================


void fired::Character::init(fired::Game *_game, sf::Vector2f _startpos, fired::World *_world) {
	game     = _game;
	settings = game->getSettings();
	app      = game->getApp();
	world    = _world;

	phys.pos          = _startpos;
	phys.velocity     = sf::Vector2f(0, 0);
	phys.acceleration = sf::Vector2f(0, PHYS_GRAVITY);
	phys.size         = sf::Vector2f(32, 48);
	phys.rect         = sf::FloatRect(phys.pos, phys.size);
	phys.onGround     = false;
	phys.isMoving     = false;

	baseStats.speed  = 180.0;
	baseStats.accel  = 1200.0;
	baseStats.jump   = 520.0;
	baseStats.aiming = 100.0;


	model.init(game, this);
	weaponCooldown = 0;

	direction = 1;
	watching  = 1;
}

//======================================================================


void fired::Character::deinit() {
	model.deinit();
}

//======================================================================


void fired::Character::update() {
	model.update();
	weaponCooldown -= frameClock;
	phys.isMoving = false;
}

//======================================================================


void fired::Character::move() {
	if (phys.isMoving) {
		phys.velocity.x += direction * frameClock * baseStats.accel;
		if (abs(phys.velocity.x) > baseStats.speed) phys.velocity.x = direction * baseStats.speed;
	} else
		phys.velocity.x = 0.0;
}

//======================================================================


void fired::Character::moveLeft() {
	direction = -1;
	phys.isMoving  = true;
}

//======================================================================


void fired::Character::moveRight() {
	direction = 1;
	phys.isMoving  = true;
}

//======================================================================


void fired::Character::jump() {
	if (phys.onGround) phys.velocity.y = -baseStats.jump;
}

//======================================================================


void fired::Character::shot(float angle) {
	if (weaponCooldown > 0) return;
	weaponCooldown = 0.2;
	world->addShot(phys.center, angle, 1000, this);
}
