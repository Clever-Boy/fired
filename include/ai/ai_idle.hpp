#ifndef __AI_IDLE
#define __AI_IDLE


#include "char.hpp"

namespace fired {
	class IdleAI : public BaseAI {
	public:
		 IdleAI(fired::Creature *_owner, fired::World *_world);
		~IdleAI() {};

		void update();
		void selectTarget() {};
	};
}
#endif
