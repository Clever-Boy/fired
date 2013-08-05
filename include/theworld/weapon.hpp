#ifndef __WEAPON
#define __WEAPON


#include <SFML/Graphics.hpp>
#include "prototypes.hpp"


namespace fired {
	struct BaseWeapon {
		float damage;
		float cooldown;

		void init();
	};



	struct Weapon {
		fired::BaseWeapon *baseWeapon;

		void init(fired::BaseWeapon *_weapon);
	};
}

#endif
