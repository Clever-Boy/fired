#ifndef __SHOT
#define __SHOT


#include <SFML/Graphics.hpp>
#include "prototypes.hpp"


namespace fired {
	struct Shot {
		sf::Vector2f pos;
		sf::Vector2f velocity;
		float        angle;
		int          damage;
		float        knockback;
		float        leftToFly;

		sf::VertexArray  line;
		fired::Character *owner;


		 Shot(sf::Vector2f _pos, float _angle, float speed, fired::Character *_owner);
		~Shot();

		bool update();
		void render();
	};
}

#endif
