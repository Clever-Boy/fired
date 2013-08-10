#ifndef __HANDLERS
#define __HANDLERS


#include "prototypes.hpp"


namespace fired {
	class Handlers {
	private:
		fired::Game *game;


	public:
		 Handlers(fired::Game *_game);
		~Handlers() {};

		void buttonStart();
		void buttonCredits();
		void buttonExit();
	};
}

#endif
