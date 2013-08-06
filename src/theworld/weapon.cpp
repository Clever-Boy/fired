#include "game.hpp"

//======================================================================


void fired::BaseWeapon::init() {
	damage   = 30;
	cooldown = 0.2;

	shotBuffer = new sf::SoundBuffer();
	shotBuffer->loadFromFile("data/snd/weapons/rifle_shot.wav");

	shotSound = new sf::Sound();
	shotSound->setBuffer(*shotBuffer);
}

//======================================================================


void fired::BaseWeapon::deinit() {
	delete shotBuffer;
	delete shotSound;
}

//======================================================================


void fired::Weapon::init(fired::BaseWeapon *_weapon) {
	damage    = _weapon->damage;
	cooldown  = _weapon->cooldown;
	shotSound = _weapon->shotSound;
}
