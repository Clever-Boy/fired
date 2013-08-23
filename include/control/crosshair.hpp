#ifndef __CROSSHAIR
#define __CROSSHAIR


#include "phys.hpp"


namespace fired {
	class Crosshair {
	private:
		fired::Camera    *cam;
		fired::Phys      *owner;

		float angle;
		sf::Vector2f pos;
		sf::Texture *crosshairTex;
		sf::Sprite  *crosshairCur;


	public:
		 Crosshair(fired::Camera *_cam, fired::Phys *_owner);
		~Crosshair();

		void update(float distance);
		void render();

		float getAngle() { return angle; };
	};
}

#endif
