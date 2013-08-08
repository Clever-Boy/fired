#include "game.hpp"

//======================================================================


void fired::BaseWeapon::deinit() {
	delete shotBuffer;
	delete shotSound;
}

//======================================================================


void fired::Weapon::init(fired::BaseWeapon *_weapon) {
	damage    = _weapon->damage;
	cooldown  = _weapon->cooldown;
	knockback = _weapon->knockback;
	shotSound = _weapon->shotSound;
}
