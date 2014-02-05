/***********************************************************************
     * File       : world_flytext.hpp
     * Created    : Aug 26, 2013
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#ifndef __WORLD_FLYTEXT
#define __WORLD_FLYTEXT


namespace fired {
	struct FlyText {
		sf::Vector2f pos;
		sf::Color    color;
		float        life;

		sf::String  *flyStr;
		sf::Text    *flyTxt;


		 FlyText(sf::Vector2f _pos, sf::Color _color, int size, const char *text);
		~FlyText();

		bool update();
		void render();
	};
}

#endif
