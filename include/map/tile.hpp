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
		int tile;


	public:
		void init(fired::Tileset *_tileset, int x, int y);
		void deinit();
		void render(sf::RenderWindow *app);

		bool isSolid() { return tileset; };
	};
}

#endif
