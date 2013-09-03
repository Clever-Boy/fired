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
