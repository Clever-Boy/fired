#include "game.hpp"


void fired::Player::init(fired::Game *_game, fired::Camera *_cam) {
	game     = _game;
	settings = game->getSettings();
	app      = game->getApp();

	character.init(_game);
	crosshair.init(_game, _cam);
}



void fired::Player::deinit() {
	character.deinit();
	crosshair.deinit();
}



void fired::Player::update() {
	character.update();
	crosshair.update(character.getStats()->aiming);

	if (cos(crosshair.getAngle()) < 0) character.setWatching(-1);
	else                               character.setWatching( 1);
}



void fired::Player::checkControls() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))     character.moveLeft();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))     character.moveRight();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) character.jump();
}
