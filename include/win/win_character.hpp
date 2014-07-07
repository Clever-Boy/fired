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


		 CharacterWindow(fired::Character *_owner);
		~CharacterWindow();

		void update();
		void render();
		void renderMain();
		void renderSkills();
		void renderStats();
		void click(sf::Vector2f mousePos);
	};
}

#endif
