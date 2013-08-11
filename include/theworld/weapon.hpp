#ifndef __WEAPON
#define __WEAPON


#include <SFML/Graphics.hpp>
#include "prototypes.hpp"


namespace fired {
	struct BaseWeapon {
		char  name[32];
		int   damage;
		int   clip;
		float cooldown;
		float reload;
		float knockback;

		sf::SoundBuffer *shotBuffer;
		sf::Sound       *shotSound;

		sf::SoundBuffer *reloadBuffer;
		sf::Sound       *reloadSound;

		~BaseWeapon();
	};



	struct Weapon {
		float damage;
		float cooldown;
		float reload;
		float knockback;
		int ammo;
		int clip;

		sf::Sound *shotSound;
		sf::Sound *reloadSound;


		Weapon(fired::BaseWeapon *_weapon);
	};
}

#endif
