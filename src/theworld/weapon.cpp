#include "game.hpp"

//======================================================================


fired::BaseWeapon::~BaseWeapon() {
	delete shotBuffer;
	delete reloadBuffer;
}

//======================================================================


fired::Weapon::Weapon(fired::BaseWeapon *_weapon) {
	damage      = _weapon->damage;
	cooldown    = _weapon->cooldown;
	reload      = _weapon->reload;
	knockback   = _weapon->knockback;
	clip        = _weapon->clip;
	automatic   = _weapon->automatic;

	shotSound = new sf::Sound();
	shotSound->setBuffer(*_weapon->shotBuffer);
	shotSound->setVolume(settings->volume.sound);

	reloadSound = new sf::Sound();
	reloadSound->setBuffer(*_weapon->reloadBuffer);
	reloadSound->setVolume(settings->volume.sound);

	ammo        = clip;
	wasShot     = false;
}

//======================================================================


fired::Weapon::~Weapon() {
	delete reloadSound;
	delete shotSound;
}
