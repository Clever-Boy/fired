#ifndef __BODYPART
#define __BODYPART


#include <SFML/Graphics.hpp>
#include "prototypes.hpp"


namespace fired {
	struct Bodypart {
		sf::Sprite   *sprite;
		sf::Texture  *texture;
		sf::Vector2f  offset;
		int          *direction;

		sf::Vector2f  animOffset;
		float         animRotation;
	};
}

#endif
