/***********************************************************************
     * File       : screen_progressbar.hpp
     * Created    : May 05, 2014
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
		void setCaption(const char *_caption, const char *_subject);

		void setLimit(int _limit) { limit = _limit;              };
		void increase()           { if (value != limit) value++; };
		void reset()              { value = 0;                   };
	};
}

#endif
