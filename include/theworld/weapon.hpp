#ifndef __WEAPON
#define __WEAPON


#include <SFML/Graphics.hpp>
#include "prototypes.hpp"


namespace fired {
	struct BaseWeapon {
		int   damage;
		float cooldown;

		sf::SoundBuffer *shotBuffer;
		sf::Sound       *shotSound;


		void init(fired::Game *game);
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
