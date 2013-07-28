#ifndef __PHYS
#define __PHYS


#include <SFML/Graphics.hpp>


#define PHYS_SCALE 16.0
#define toPhys(x)   (x)/PHYS_SCALE
#define fromPhys(x) (x)*PHYS_SCALE



namespace fired {
	struct Phys {
		sf::Vector2f  size;
		sf::Vector2f  pos;
		bool          onGround;
	};
}

#endif
