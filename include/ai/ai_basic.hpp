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
