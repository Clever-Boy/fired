#ifndef __SHOT
#define __SHOT


#include <SFML/Graphics.hpp>
#include "prototypes.hpp"


namespace fired {
	struct Shot {
		sf::Vector2f pos;
		sf::Vector2f velocity;

		sf::RectangleShape *line;
		fired::Character   *owner;


		void init(sf::Vector2f _pos, float angle, float speed, fired::Character *_owner);
		void deinit();
		bool update(sf::RenderWindow *app);
		void render(sf::RenderWindow *app);
	};
}

#endif
