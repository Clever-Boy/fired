/***********************************************************************
     * File       : screen_base.hpp
     * Created    : Aug 23, 2013
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#ifndef __SCREEN_BASE
#define __SCREEN_BASE

namespace fired {
	struct GameScreen {
		virtual ~GameScreen()                {};
		virtual void update()                {};
		virtual void processEvent(sf::Event) {};
		virtual void applySoundSettings()    {};
		virtual void applyVideoSettings()    {};
	};
}

#endif
