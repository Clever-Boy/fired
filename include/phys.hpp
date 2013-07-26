#ifndef __PHYS
#define __PHYS


#include <SFML/Graphics.hpp>


#define PHYS_GRAVITY  512.0
#define PHYS_MAX_FALL 5000.0



namespace fired {
	struct Phys {
		sf::Vector2f  size;
		sf::Vector2f  pos;
		sf::Vector2f  velocity;
		sf::Vector2f  acceleration;
	};
}

#endif
