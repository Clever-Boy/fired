/***********************************************************************
     * File       : item_weapon.hpp
     * Created    : Sep 01, 2013
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#ifndef __ITEM_WEAPON
#define __ITEM_WEAPON


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
		int   subtype;

		bool  automatic;

		sf::Sound           *shotSound;
		fired::BaseBodypart *bodypart;
	};
}

#endif
