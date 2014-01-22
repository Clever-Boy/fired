/***********************************************************************
     * File       : creditsscr.hpp
     * Created    : Jul 22, 2013
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#ifndef __CREDITSSCR
#define __CREDITSSCR


namespace fired {
	struct CreditsScr : GameScreen {
		std::vector<sf::Text*> credits;
		float yOffset;


		 CreditsScr();
		~CreditsScr();

		void update();
		void render();
		void click(sf::Vector2i pos);
		void processEvent(sf::Event event);
	};
}

#endif
