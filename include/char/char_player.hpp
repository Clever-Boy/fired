/***********************************************************************
     * File       : char_player.hpp
     * Created    : Jul 27, 2013
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#ifndef __CHAR_PLAYER
#define __CHAR_PLAYER


#include "char_base.hpp"


namespace fired {
	struct Player {
		float             deadTime;

		fired::Character *character;
		fired::Crosshair *crosshair;


		 Player(fired::Camera *_cam, fired::Crosshair *_crosshair, fired::World *world);
		~Player();

		void update();
		void checkControls();
	};
}

#endif
