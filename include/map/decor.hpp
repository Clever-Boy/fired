#ifndef __TILE
#define __DECOR


#define TILE_SIZE 16.0


#include <SFML/Graphics.hpp>
#include "prototypes.hpp"
#include "tileset.hpp"


namespace fired {
	struct MapDecor {
		int ID;
		sf::Vector2f pos;
	};


	class Decor {
	private:
		sf::Vector2f pos;
		sf::Sprite  *sprite;
		sf::Color    color;


	public:
		void render();
	};
}

#endif
