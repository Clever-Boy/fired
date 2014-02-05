/***********************************************************************
     * File       : screen_start.hpp
     * Created    : Jul 22, 2013
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#ifndef __SCREEN_START
#define __SCREEN_START


namespace fired {
	struct StartScr : GameScreen {
		std::vector<sf::Texture*> textures;
		std::vector<sf::Sprite*> sprites;

		float        timeOffset;
		unsigned int index;


		 StartScr();
		~StartScr();

		void update();
		void render();
		void processEvent(sf::Event event);
	};
}

#endif
