#ifndef __HANDLERS
#define __HANDLERS


namespace fired {
	struct Handlers {
		void buttonStart();
		void buttonCredits();
		void buttonExit();
	};


	typedef void (Handlers::*Handler)(void);
}

#endif
