/***********************************************************************
     * File       : stats.hpp
     * Created    : Jul 25, 2013
     * Copyright  : (C) 2013 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#ifndef __STATS
#define __STATS


namespace fired {
	struct CharacterStats {
		float speed;
		float accel;
		float aimrange;
		float jump;

		int maxHP;
		int HP;

		int armor;
	};
}

#endif
