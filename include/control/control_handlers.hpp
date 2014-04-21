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
		void buttonStartBuilding();
		void buttonStartMine();
		void buttonStartGraveyard();
		void buttonCredits();
		void buttonExit();
	};


	typedef void (Handlers::*Handler)();
}

#endif
