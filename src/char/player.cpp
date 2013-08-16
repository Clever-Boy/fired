#include "game.hpp"

//======================================================================


fired::Player::Player(fired::Camera *_cam, sf::Vector2f _startpos, fired::World *world) {
	startPos = _startpos;
	deadTime = 0;

	character = new fired::Character(_cam, _startpos, world, world->getCreature("player"));
	crosshair = new fired::Crosshair(_cam, &character->phys);
}

//======================================================================


fired::Player::~Player() {
	delete character;
	delete crosshair;
}

//======================================================================


void fired::Player::update() {
	if (character->isDead()) {
		if (deadTime < PLAYER_RESPAWN_TIME) {
			deadTime += frameClock;
			return;
		} else {
			character->respawn(startPos);
			deadTime = 0;
		}
	}

	character->setAiming(crosshair->getAngle());

	character->update();
	crosshair->update(character->getStats()->aimrange);
}

//======================================================================


void fired::Player::checkControls() {
	if (character->isDead()) return;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))     character->moveLeft();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))     character->moveRight();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) character->jump();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))     character->reload();

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))     character->shot();
	if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))    character->unshot();
}
