#include "game.hpp"

//======================================================================


fired::BaseWeapon::~BaseWeapon() {
	if (type == WEAPON_TYPE_RANGED) {
		delete shotBuffer;
		delete reloadBuffer;
	}
}

//======================================================================


fired::Weapon::Weapon(fired::BaseWeapon *_weapon) {
	damage      = _weapon->damage;
	range       = _weapon->range;
	cooldown    = _weapon->cooldown;
	speed       = _weapon->speed;
	reload      = _weapon->reload;
	knockback   = _weapon->knockback;
	clip        = _weapon->clip;
	type        = _weapon->type;
	automatic   = _weapon->automatic;

	if (type == WEAPON_TYPE_RANGED) {
		shotSound = new sf::Sound();
		shotSound->setBuffer(*_weapon->shotBuffer);
		shotSound->setVolume(settings->volume.sound);

		reloadSound = new sf::Sound();
		reloadSound->setBuffer(*_weapon->reloadBuffer);
		reloadSound->setVolume(settings->volume.sound);
	}

	ammo        = clip;
	wasShot     = false;
}

//======================================================================


fired::Weapon::~Weapon() {
	if (type == WEAPON_TYPE_RANGED) {
		delete reloadSound;
		delete shotSound;
	}
}
