#ifndef __PHYS
#define __PHYS


#include <SFML/Graphics.hpp>


namespace fired {
	struct Phys {
		sf::Vector2f  size;
		sf::Vector2f  pos;
		bool          onGround;
	};
}

#endif
