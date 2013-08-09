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
		float        scaleX;
		float        scaleY;


		void init(fired::Bodypart *bodyPart, float scale, sf::Vector2f position);
		void deinit() {};
		void update(sf::RenderWindow *app);
		void render(sf::RenderWindow *app);
	};
}

#endif
