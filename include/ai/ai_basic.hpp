/***********************************************************************
     * File       : ai_basic.hpp
     * Created    : Aug 17, 2013
     * Copyright  : (C) 2013 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#ifndef __AI_MEELE
#define __AI_MELEE


#include "ai_base.hpp"


namespace fired {
	struct BasicAI : BaseAI {
		 BasicAI(fired::Creature *_owner, fired::World *_world);
		~BasicAI() {};

		void update();
		void selectTarget();
	};
}
#endif
