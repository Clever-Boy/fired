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
		 CritterAI(fired::Creature *_owner, fired::World *_world) : BaseAI(_owner, _world) {};
		~CritterAI() {};

		void update();
	};
}

#endif
