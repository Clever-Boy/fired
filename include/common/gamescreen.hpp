/***********************************************************************
     * File       : gamescreen.hpp
     * Created    : Aug 23, 2013
     * Copyright  : (C) 2013 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#ifndef __GAMESCREEN
#define __GAMESCREEN

namespace fired {
	struct GameScreen {
		virtual ~GameScreen()                {};
		virtual void update()                {};
		virtual void processEvent(sf::Event) {};
	};
}

#endif
