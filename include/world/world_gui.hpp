/***********************************************************************
     * File       : world_gui.hpp
     * Created    : Aug 26, 2013
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#ifndef __WORLD_GUI
#define __WORLD_GUI


#include "char.hpp"


namespace fired {
	struct GUI {
		fired::Character *owner;

		int          barHeight;
		int          barWidth;

		sf::Texture *barTex;
		sf::Sprite  *barSpr;

		sf::RectangleShape *bar;
		sf::String         *str;
		sf::Text           *txt;


		 GUI(fired::Character *_owner);
		~GUI();

		void update();
		void renderBase();
		void renderHP();
		void renderXP();
		void renderAmmo();
		void renderCooldown();

		sf::Vector2f getBounds();
	};
}

#endif
