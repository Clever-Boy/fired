#ifndef __WEAPON
#define __WEAPON


namespace fired {
	struct BaseWeapon {
		char  name[64];
		char  caption[64];
		float cooldown;
		float range;
		float speed;
		float knockback;
		int   damage;
		int   type;
		int   automatic;

		sf::Sound           *shotSound;
		fired::GameSprite   *shotSprite;
		fired::BaseBodypart *bodypart;
	};
}

#endif
