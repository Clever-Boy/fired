/***********************************************************************
     * File       : ai_idle.hpp
     * Created    : Aug 12, 2013
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#ifndef __AI_IDLE
#define __AI_IDLE


#include "ai_base.hpp"


namespace fired {
	struct IdleAI : BaseAI {
		 IdleAI(fired::Creature *_owner, fired::World *_world);
		~IdleAI() {};

		void update();
		void selectTarget() {};
	};
}
#endif
