#include "game.hpp"

//======================================================================


void fired::Player::init(fired::Game *_game, fired::Camera *_cam, sf::Vector2f _startpos, fired::World *world) {
	game     = _game;
	settings = game->getSettings();
	app      = game->getApp();

	character.init(_game, _startpos, world);
	crosshair.init(_game, _cam, &character.phys);
}

//======================================================================


void fired::Player::deinit() {
	character.deinit();
	crosshair.deinit();
}

//======================================================================


void fired::Player::update() {
	character.update();
	crosshair.update(character.getStats()->aimrange);
	character.setAiming(crosshair.getAngle());
}

//======================================================================


void fired::Player::checkControls() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))     character.moveLeft();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))     character.moveRight();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) character.jump();
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))     character.shot();

	character.move();
}
