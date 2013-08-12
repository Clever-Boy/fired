#include "game.hpp"

//======================================================================


fired::Player::Player(fired::Game *_game, fired::Camera *_cam, sf::Vector2f _startpos, fired::World *world) {
	game     = _game;
	settings = game->getSettings();
	app      = game->getApp();

	character = new fired::Character(_game, _cam, _startpos, world, world->getCreature("player"));
	crosshair = new fired::Crosshair(_game, _cam, &character->phys);
}

//======================================================================


fired::Player::~Player() {
	delete character;
	delete crosshair;
}

//======================================================================


void fired::Player::update() {
	character->update();
	crosshair->update(character->getStats()->aimrange);
	character->setAiming(crosshair->getAngle());
}

//======================================================================


void fired::Player::checkControls() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))     character->moveLeft();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))     character->moveRight();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) character->jump();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))     character->reload();

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))     character->shot();
	if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))    character->unshot();
}
