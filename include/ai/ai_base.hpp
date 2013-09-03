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
