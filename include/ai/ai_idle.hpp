#ifndef __AI_IDLE
#define __AI_IDLE


#include "char.hpp"

namespace fired {
	class IdleAI : public BaseAI {
	public:
		 IdleAI(fired::Creature *_owner) { owner = _owner; };
		~IdleAI() {};

		void update();
	};
}
#endif
