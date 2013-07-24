#ifndef __TILE
#define __TILE


#define TILE_SIZE        16.0
#define TILE_SIZE_ORIGIN 32.0


#include <SFML/Graphics.hpp>
#include "prototypes.hpp"


namespace fired {
	class Tile {
	private:
		fired::Tileset *tileset;
		sf::Vector2f pos;


	public:
		void init(fired::Tileset *_tileset);
		void deinit();
		void render();
	};
}

#endif
