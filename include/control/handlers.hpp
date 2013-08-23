#ifndef __HANDLERS
#define __HANDLERS


namespace fired {
	class Handlers {
	public:
		void buttonStart();
		void buttonCredits();
		void buttonExit();
	};


	typedef void (Handlers::*Handler)(void);
}

#endif
