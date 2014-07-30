/***********************************************************************
     * File       : ai_critter.hpp
     * Created    : Aug 17, 2013
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#ifndef __AI_CRITTER
#define __AI_CRITTER


#include "ai_base.hpp"


namespace fired {
	struct CritterAI : BaseAI {
		int moving;
		int jumping;

		fired::Timer moveTimer;
		fired::Timer jumpTimer;


		 CritterAI(fired::Creature *_owner, fired::World *_world);
		~CritterAI() {};

		void update();
	};
}

#endif
