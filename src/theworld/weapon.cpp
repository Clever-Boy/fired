#include "game.hpp"

//======================================================================


void fired::BaseWeapon::init() {
	damage   = 30;
	cooldown = 0.2;
}

//======================================================================


void fired::Weapon::init(fired::BaseWeapon *_weapon) {
	baseWeapon = _weapon;
}
