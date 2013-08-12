#ifndef __WEAPON
#define __WEAPON


#include <SFML/Graphics.hpp>
#include "prototypes.hpp"


namespace fired {
	struct BaseWeapon {
		char  name[32];
		char  model[32];
		int   damage;
		int   clip;
		float cooldown;
		float reload;
		float knockback;
		int   automatic;

		sf::SoundBuffer *shotBuffer;
		sf::SoundBuffer *reloadBuffer;

		~BaseWeapon();
	};



	struct Weapon {
		float damage;
		float cooldown;
		float reload;
		float knockback;
		int   ammo;
		int   clip;
		int   automatic;

		bool  wasShot;

		sf::Sound *shotSound;
		sf::Sound *reloadSound;


		 Weapon(fired::BaseWeapon *_weapon);
		~Weapon();
	};
}

#endif
