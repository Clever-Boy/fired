#ifndef __THEMAP
#define __THEMAP


#include <SFML/Graphics.hpp>
#include "tile.hpp"
#include "prototypes.hpp"


namespace fired {
	class Map {
	private:
		fired::Tile *tiles[100][100];


	public:
		void init();
		void deinit();
		void render();
	};
}

#endif
