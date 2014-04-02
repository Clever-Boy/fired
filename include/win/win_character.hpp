/***********************************************************************
     * File       : win_character.hpp
     * Created    : Aug 28, 2013
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#ifndef __WIN_CHARACTER
#define __WIN_CHARACTER


#include "win_base.hpp"


namespace fired {
	struct CharacterWindow {
		fired::Window              *win;
		fired::Character           *owner;

		sf::Text *text;


		 CharacterWindow(fired::Character *_owner);
		~CharacterWindow();

		void update();
		void render();
		void renderMain();
		void renderSkills();
		void renderStats();
		void renderText(float x, float y, const char *caption, bool rightAligned, sf::Color color);
		void click(sf::Vector2f mousePos);
	};
}

#endif
