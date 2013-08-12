#ifndef __BASEAI
#define __BASEAI


#include "char.hpp"

namespace fired {
	class BaseAI {
	protected:
		fired::Creature *owner;


	public:
		 BaseAI(fired::Creature *_owner) { owner = _owner; };

		virtual ~BaseAI() {};
		virtual void update() {};
	};
}
#endif
