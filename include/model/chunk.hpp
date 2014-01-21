#ifndef __CHUNK
#define __CHUNK


#include "bodypart.hpp"


namespace fired {
	struct Chunk {
		fired::BaseBodypart *base;
		fired::World        *world;
		fired::Phys          phys;

		sf::Color    color;
		float        rotationSpeed;
		float        rotation;
		float        scaleX;
		float        scaleY;
		float        lifetime;


		Chunk(fired::Bodypart *bodyPart, float scale, sf::Vector2f position, sf::Vector2f speed, fired::World *_world);

		bool update();
		void render();
	};
}

#endif
