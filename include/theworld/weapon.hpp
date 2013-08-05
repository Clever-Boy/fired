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
		float damage;
		float cooldown;
		int ammo;

		void init(fired::BaseWeapon *_weapon);
	};
}

#endif
