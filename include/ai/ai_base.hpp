#ifndef __AI_BASE
#define __AI_BASE


#include "char.hpp"

namespace fired {
	class BaseAI {
	protected:
		fired::Creature *owner;


	public:
		 BaseAI() {};

		virtual ~BaseAI() {};
		virtual void update() {};
	};
}
#endif
