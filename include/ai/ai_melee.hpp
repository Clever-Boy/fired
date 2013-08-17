#ifndef __AI_MEELE
#define __AI_MELEE


#include "char.hpp"

namespace fired {
	class MeleeAI : public BaseAI {
	public:
		 MeleeAI(fired::Creature *_owner, fired::World *_world);
		~MeleeAI() {};

		void update();
		void selectTarget();
	};
}
#endif
