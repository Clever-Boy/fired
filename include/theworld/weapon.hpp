#ifndef __WEAPON
#define __WEAPON


#include <SFML/Graphics.hpp>
#include "prototypes.hpp"


namespace fired {
	struct BaseWeapon {
		char  name[32];
		int   damage;
		float cooldown;
		float knockback;

		sf::SoundBuffer *shotBuffer;
		sf::Sound       *shotSound;

		~BaseWeapon();
	};



	struct Weapon {
		float damage;
		float cooldown;
		float knockback;
		int ammo;

		sf::Sound *shotSound;


		Weapon(fired::BaseWeapon *_weapon);
	};
}

#endif
