#ifndef __PLAYER
#define __PLAYER


namespace fired {
	class Player;
}


#include <SFML/Graphics.hpp>
#include "prototypes.hpp"
#include "phys.hpp"
#include "character.hpp"
#include "stats.hpp"


#define PLAYER_RESPAWN_TIME 3.0f


namespace fired {
	class Player {
	private:
		sf::Vector2f      startPos;
		float             deadTime;

		fired::Character *character;
		fired::Crosshair *crosshair;


	public:
		 Player(fired::Camera *_cam, sf::Vector2f _startpos, fired::World *world);
		~Player();

		void update();

		void checkControls();
		fired::Phys *getPhys() { return &character->phys; };
		fired::Character *getChar() { return character; };
	};
}

#endif
