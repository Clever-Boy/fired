#ifndef __WEAPON
#define __WEAPON


#include <SFML/Graphics.hpp>
#include "prototypes.hpp"


#define WEAPON_TYPE_RANGED 1
#define WEAPON_TYPE_MELEE  2
#define WEAPON_TYPE_BROAD  3


namespace fired {
	struct BaseWeapon {
		char  name[32];
		char  model[32];
		float cooldown;
		float range;
		float speed;
		float reload;
		float knockback;
		int   damage;
		int   type;
		int   clip;
		int   automatic;

		sf::Sprite      *shotSprite;
		sf::SoundBuffer *shotBuffer;
		sf::SoundBuffer *reloadBuffer;

		~BaseWeapon();
	};



	struct Weapon {
		float damage;
		float cooldown;
		float range;
		float speed;
		float reload;
		float knockback;
		int   type;
		int   ammo;
		int   clip;
		int   automatic;

		bool  wasShot;

		sf::Sprite *shotSprite;
		sf::Sound  *shotSound;
		sf::Sound  *reloadSound;


		 Weapon(fired::BaseWeapon *_weapon);
		~Weapon();
	};
}

#endif
