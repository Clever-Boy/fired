#ifndef __AI_BASE
#define __AI_BASE


#include "char.hpp"

namespace fired {
	class BaseAI {
	protected:
		fired::Creature  *owner;
		fired::Character *target;
		fired::World     *world;


	public:
		 BaseAI() {};

		virtual ~BaseAI()           {};
		virtual void update()       {};
		virtual void selectTarget() {};
	};
}
#endif
