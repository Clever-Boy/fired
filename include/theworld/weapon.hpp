#ifndef __WEAPON
#define __WEAPON


#include <SFML/Graphics.hpp>
#include "prototypes.hpp"


namespace fired {
	struct BaseWeapon {
		float damage;
		float cooldown;

		sf::SoundBuffer *shotBuffer;
		sf::Sound       *shotSound;


		void init();
		void deinit();
	};



	struct Weapon {
		float damage;
		float cooldown;
		int ammo;

		sf::Sound *shotSound;


		void init(fired::BaseWeapon *_weapon);
	};
}

#endif
