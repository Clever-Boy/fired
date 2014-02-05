/***********************************************************************
     * File       : control_mouse.hpp
     * Created    : Jul 26, 2013
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#ifndef __CONTROL_MOUSE
#define __CONTROL_MOUSE


namespace fired {
	struct Mouse {
		sf::Vector2f pos;
		sf::Texture *mouseTex;
		sf::Sprite  *mouseCur;


		 Mouse();
		~Mouse();

		void update();
		void render();
	};
}

#endif
