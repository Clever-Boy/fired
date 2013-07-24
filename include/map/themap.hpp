#ifndef __THEMAP
#define __THEMAP


#include <SFML/Graphics.hpp>
#include "tile.hpp"
#include "tileset.hpp"
#include "prototypes.hpp"


namespace fired {
	class Map {
	private:
		fired::Game    *game;
		fired::Tileset tileset;
		fired::Tile    tiles[100][100];


	public:
		void init(fired::Game *_game);
		void deinit();
		void render();
	};
}

#endif
