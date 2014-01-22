/***********************************************************************
     * File       : ai_base.hpp
     * Created    : Aug 12, 2013
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#ifndef __AI_BASE
#define __AI_BASE


#include "char.hpp"

namespace fired {
	struct BaseAI {
		fired::Creature  *owner;
		fired::Character *target;
		fired::World     *world;


		 BaseAI() {};

		virtual ~BaseAI()           {};
		virtual void update()       {};
		virtual void selectTarget() {};
	};
}
#endif
