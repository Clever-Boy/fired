#include "game.hpp"

//======================================================================


fired::Player::Player(fired::Camera *_cam, sf::Vector2f _startpos, fired::Crosshair *_crosshair, fired::World *world) {
	startPos = _startpos;
	deadTime = 0;

	character = new fired::Character(_cam, _startpos, world, world->getCreature("player"));
	crosshair = _crosshair;
	crosshair->owner = &character->phys;
}

//======================================================================


fired::Player::~Player() {
	delete character;
}

//======================================================================


void fired::Player::update() {
	if (character->dead) {
		if (deadTime < PLAYER_RESPAWN_TIME) {
			deadTime += frameClock;
			return;
		} else {
			character->respawn(startPos);
			deadTime = 0;
		}
	}

	character->setAiming(crosshair->angle);

	character->update();
}

//======================================================================


void fired::Player::checkControls() {
	if (character->dead) return;
	character->phys.jumpdown = false;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))     character->moveLeft();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))     character->moveRight();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))     character->jumpdown();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) character->jump();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))     character->reload();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))     character->interact();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))     character->swapWeapons();

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))     character->shot();
	else                                                 character->unshot();
}
