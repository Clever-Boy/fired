#include "game.hpp"

//======================================================================


fired::BaseWeapon::~BaseWeapon() {
	delete shotBuffer;
	delete shotSound;

	delete reloadBuffer;
	delete reloadSound;
}

//======================================================================


fired::Weapon::Weapon(fired::BaseWeapon *_weapon) {
	damage      = _weapon->damage;
	cooldown    = _weapon->cooldown;
	reload      = _weapon->reload;
	knockback   = _weapon->knockback;
	clip        = _weapon->clip;
	automatic   = _weapon->automatic;
	shotSound   = _weapon->shotSound;
	reloadSound = _weapon->reloadSound;

	ammo        = clip;
	wasShot     = false;
}
