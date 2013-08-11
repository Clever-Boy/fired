#include "game.hpp"

//======================================================================


fired::BaseWeapon::~BaseWeapon() {
	delete shotBuffer;
	delete shotSound;
}

//======================================================================


fired::Weapon::Weapon(fired::BaseWeapon *_weapon) {
	damage    = _weapon->damage;
	cooldown  = _weapon->cooldown;
	reload    = _weapon->reload;
	knockback = _weapon->knockback;
	clip      = _weapon->clip;
	shotSound = _weapon->shotSound;
	ammo      = clip;
}
