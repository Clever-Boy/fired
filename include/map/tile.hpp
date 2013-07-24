#ifndef __TILE
#define __TILE


#define TILE_SIZE 24


#include <SFML/Graphics.hpp>
#include "prototypes.hpp"


namespace fired {
	class Tile {
	private:
		sf::Vector2f pos;


	public:
		void init();
		void deinit();
		void render();
	};
}

#endif
