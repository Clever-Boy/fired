#include "game.hpp"

//======================================================================


void fired::BaseWeapon::init() {
	damage = 30;
}

//======================================================================


void fired::Weapon::init(fired::BaseWeapon *_weapon) {
	baseWeapon = _weapon;
}
