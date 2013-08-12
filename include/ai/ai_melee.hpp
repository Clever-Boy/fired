#ifndef __AI_MEELE
#define __AI_MELEE


#include "char.hpp"

namespace fired {
	class MeleeAI : public BaseAI {
	public:
		 MeleeAI(fired::Creature *_owner) { owner = _owner; };
		~MeleeAI() {};

		void update();
	};
}
#endif
