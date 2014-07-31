/***********************************************************************
     * File       : char_player.cpp
     * Created    : Jul 27, 2013
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#include "game.hpp"



/***********************************************************************
     * Player
     * constructor

***********************************************************************/
fired::Player::Player(fired::Camera *_cam, fired::Crosshair *_crosshair, fired::World *world) {
	deadTime = 0;

	character = new fired::Character(_cam, world->map->getPlayerSpawn(), world, container->getCreature("Player"), "data/chars/player.chr");
	crosshair = _crosshair;
	crosshair->owner = &character->phys;

	sf::Listener::setDirection(0.0f, 0.0f, -1.0f);
}



/***********************************************************************
     * Player
     * destructor

***********************************************************************/
fired::Player::~Player() {
	saveChar(character, "data/chars/player.chr");
	delete character;
}



/***********************************************************************
     * Player
     * update

***********************************************************************/
void fired::Player::update() {
	if (character->dead) {
		if (deadTime < PLAYER_RESPAWN_TIME) {
			deadTime += frameClock;
			return;
		} else {
			character->respawn(character->world->map->getPlayerSpawn());
			deadTime = 0;
		}
	}

	character->setAiming(crosshair->angle);
	character->update();

	sf::Listener::setPosition(character->phys.pos.x, character->phys.pos.y, 0.0f);
}



/***********************************************************************
     * Player
     * checkControls

***********************************************************************/
void fired::Player::checkControls() {
	if (character->dead) return;
	character->phys.jumpdown = false;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))     character->moveLeft();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))     character->moveRight();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))     character->jumpdown();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) character->jump();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))     character->interact();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))     character->swapWeapons();

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))     character->shot();
	else                                                 character->unshot();
}
