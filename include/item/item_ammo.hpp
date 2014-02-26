/***********************************************************************
     * File       : item_ammo.hpp
     * Created    : Feb 25, 2014
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#ifndef __ITEM_AMMO
#define __ITEM_AMMO


namespace fired {
	enum ShotTracer {
		stNone,
		stSmoke
	};

	struct BaseAmmo {
		char  name[64];
		char  caption[64];

		float explosionRadius;
		int   damage;
		int   subtype;
		bool  explosive;

		ShotTracer tracer;

		fired::GameSprite   *shotSprite;
	};
}

#endif
