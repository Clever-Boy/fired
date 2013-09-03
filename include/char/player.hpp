#ifndef __PLAYER
#define __PLAYER


#include "character.hpp"


namespace fired {
	struct Player {
		sf::Vector2f      startPos;
		float             deadTime;

		fired::Character *character;
		fired::Crosshair *crosshair;


		 Player(fired::Camera *_cam, sf::Vector2f _startpos, fired::Crosshair *_crosshair, fired::World *world);
		~Player();

		void update();
		void checkControls();
	};
}

#endif
