/***********************************************************************
     * File       : screen_loading.hpp
     * Created    : May 05, 2014
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#ifndef __SCREEN_LOADING
#define __SCREEN_LOADING


namespace fired {
	struct LoadingScr : GameScreen {
		fired::ProgressBar *mainBar;
		fired::ProgressBar *secBar;

		sf::Texture* texture;
		sf::Sprite*  sprite;

		float        timeOffset;


		 LoadingScr();
		~LoadingScr();

		void update();
		void render();
		void processEvent(sf::Event) {};
	};
}

#endif
