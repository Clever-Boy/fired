/***********************************************************************
     * File       : screen_progressbar.hpp
     * Created    : Jul 22, 2013
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#ifndef __SCREEN_PROGRESSBAR
#define __SCREEN_PROGRESSBAR


namespace fired {
	struct ProgressBar {
		sf::Vector2f pos;


		 ProgressBar(sf::Vector2f _pos);
		~ProgressBar();

		void render();
	};
}

#endif
