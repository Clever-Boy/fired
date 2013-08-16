#ifndef __PHYS
#define __PHYS


#include <SFML/Graphics.hpp>


#define PHYS_GRAVITY        1500.0
#define PHYS_MAX_FALL       2500.0
#define PHYS_TUNNEL_TIME    8.0
#define PHYS_TUNNEL_CHUNK   3.0
#define PHYS_SAFE_FALL      900.0
#define PHYS_FRICTION_ACCEL 800.0
#define PHYS_EPSILON        3.0


namespace fired {
	struct Phys {
		sf::Vector2f  size;
		sf::Vector2f  pos;
		sf::Vector2f  velocity;
		sf::Vector2f  acceleration;

		sf::Vector2f  headSize;
		sf::Vector2f  headOffset;

		sf::FloatRect rect;
		sf::FloatRect head;
		sf::Vector2f  center;
		bool isMoving;
		bool onGround;


		void calculate();
	};
}

#endif
