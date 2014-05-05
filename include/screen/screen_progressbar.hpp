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
		sf::Vector2f  pos;
		sf::Text     *caption;

		int value;
		int limit;


		 ProgressBar(sf::Vector2f _pos);
		~ProgressBar();

		void render();

		void setLimit(int _limit) {limit = _limit;};
		void increase()           {if (value != limit) value++;};
		void setCaption(const char *_caption, const char *_subject);
	};
}

#endif
