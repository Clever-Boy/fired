#ifndef __PHYS
#define __PHYS


#include <SFML/Graphics.hpp>


#define PHYS_GRAVITY      1500.0
#define PHYS_MAX_FALL     2500.0
#define PHYS_TUNNEL_CHUNK 8.0


namespace fired {
	struct Phys {
		sf::Vector2f  size;
		sf::Vector2f  pos;
		sf::Vector2f  velocity;
		sf::Vector2f  acceleration;

		sf::FloatRect rect;
		bool onGround;
	};
}

#endif
