#ifndef __PLAYER
#define __PLAYER


#include "character.hpp"


namespace fired {
	class Player {
	private:
		sf::Vector2f      startPos;
		float             deadTime;

		fired::Character *character;
		fired::Crosshair *crosshair;


	public:
		 Player(fired::Camera *_cam, sf::Vector2f _startpos, fired::Crosshair *_crosshair, fired::World *world);
		~Player();

		void update();

		void checkControls();
		fired::Phys *getPhys() { return &character->phys; };
		fired::Character *getChar() { return character; };
	};
}

#endif
