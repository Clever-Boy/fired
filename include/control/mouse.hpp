/***********************************************************************
     * File       : mouse.hpp
     * Created    : Jul 26, 2013
     * Copyright  : (C) 2013 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#ifndef __MOUSE
#define __MOUSE


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
