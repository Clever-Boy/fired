/***********************************************************************
     * File       : win_base.hpp
     * Created    : Aug 26, 2013
     * Copyright  : (C) 2013 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#ifndef __WIN_BASE
#define __WIN_BASE


namespace fired {
	struct Window {
		sf::RectangleShape *window;

		sf::Vector2f size;
		sf::Vector2f offset;


		 Window(sf::Vector2f _size);
		~Window();

		void render();
		void setOffset(sf::Vector2f newOffset);
		void setSize(sf::Vector2f newSize);
	};
}

#endif
