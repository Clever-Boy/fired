/***********************************************************************
     * File       : control_handlers.hpp
     * Created    : Jul 26, 2013
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#ifndef __CONTROL_HANDLERS
#define __CONTROL_HANDLERS


namespace fired {
	struct Handlers {
		void buttonStart();
		void buttonCredits();
		void buttonExit();
	};


	typedef void (Handlers::*Handler)(void);
}

#endif
