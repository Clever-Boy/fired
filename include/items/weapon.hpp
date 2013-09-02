#ifndef __WEAPON
#define __WEAPON


namespace fired {
	struct BaseWeapon {
		char  name[64];
		char  model[64];
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
