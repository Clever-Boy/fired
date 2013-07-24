#ifndef __HANDLERS
#define __HANDLERS


#include "prototypes.hpp"


namespace fired {
	class Handlers {
	private:
		fired::Game *game;


	public:
		void init(fired::Game *_game);

		void buttonCredits();
		void buttonExit();
	};
}

#endif
