#ifndef __AI_MEELE
#define __AI_MELEE


#include "ai_base.hpp"


namespace fired {
	class BasicAI : public BaseAI {
	public:
		 BasicAI(fired::Creature *_owner, fired::World *_world);
		~BasicAI() {};

		void update();
		void selectTarget();
	};
}
#endif
