/***********************************************************************
     * File       : crosshair.hpp
     * Created    : Jul 27, 2013
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#ifndef __CROSSHAIR
#define __CROSSHAIR


#include "phys.hpp"


namespace fired {
	struct Crosshair {
		fired::Camera    *cam;
		fired::Phys      *owner;

		float angle;
		sf::Vector2f pos;
		sf::Texture *crosshairTex;
		sf::Sprite  *crosshairCur;


		 Crosshair(fired::Camera *_cam);
		~Crosshair();

		void update(float distance);
		void render();
	};
}

#endif
