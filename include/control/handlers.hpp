/***********************************************************************
     * File       : handlers.hpp
     * Created    : Jul 26, 2013
     * Copyright  : (C) 2013 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
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
