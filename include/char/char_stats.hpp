/***********************************************************************
     * File       : char_stats.hpp
     * Created    : Jul 25, 2013
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#ifndef __CHAR_STATS
#define __CHAR_STATS


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
