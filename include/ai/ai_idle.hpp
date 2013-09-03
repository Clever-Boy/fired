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
