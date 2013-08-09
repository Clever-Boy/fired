#ifndef __CHUNK
#define __CHUNK


#include <SFML/Graphics.hpp>
#include "prototypes.hpp"


namespace fired {
	struct Chunk {
		fired::BaseBodypart *base;

		sf::Vector2f speed;
		sf::Vector2f pos;
		float        rotationSpeed;
		float        rotation;


		void init(fired::Bodypart *bodyPart);
	};
}

#endif
