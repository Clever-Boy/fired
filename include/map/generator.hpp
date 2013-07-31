#ifndef __GENERATOR
#define __GENERATOR


#include <SFML/Graphics.hpp>
#include "tile.hpp"
#include "tileset.hpp"
#include "prototypes.hpp"


namespace fired {
	class MapGenerator {
	private:
		fired::MapTile  **tiles;
		int sizeX;
		int sizeY;

		void deinit();
		void save(const char* filename);


	public:
		void generate();
	};
}

#endif
