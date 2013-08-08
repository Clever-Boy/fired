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

		void deinit();
	};



	struct Weapon {
		float damage;
		float cooldown;
		float knockback;
		int ammo;

		sf::Sound *shotSound;


		void init(fired::BaseWeapon *_weapon);
	};
}

#endif
