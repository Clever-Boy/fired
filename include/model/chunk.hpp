#ifndef __CHUNK
#define __CHUNK


#define CHUNK_LIFETIME      2.0
#define CHUNK_DISAPPEARTIME 1.5


#include <SFML/Graphics.hpp>
#include "prototypes.hpp"


namespace fired {
	struct Chunk {
		fired::BaseBodypart *base;
		fired::Phys          phys;

		sf::Vector2f speed;
		sf::Vector2f pos;
		float        rotationSpeed;
		float        rotation;
		float        scaleX;
		float        scaleY;
		float        lifetime;


		void init(fired::Bodypart *bodyPart, float scale, sf::Vector2f position, sf::Vector2f speed);
		void deinit() {};
		bool update(sf::RenderWindow *app);
		void render(sf::RenderWindow *app);
	};
}

#endif
