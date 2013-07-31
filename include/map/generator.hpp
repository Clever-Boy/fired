#ifndef __GENERATOR
#define __GENERATOR


#include <SFML/Graphics.hpp>
#include "tile.hpp"
#include "tileset.hpp"
#include "prototypes.hpp"


namespace fired {
	class MapGenerator {
	private:
		fired::MapTile **tiles;
		sf::Vector2f     startPos;
		int sizeX;
		int sizeY;

		void deinit();
		void save(const char* filename);

		void genLandscape(int areaStart, int areaEnd, int horizon, int max, int min);
		void genHills(int areaStart, int areaEnd, int horizon);
		void genClear();
		void genPlayer();

		void genHill(int areaStart, int areaWidth, int height, int horizon);
		void genBar(int x, int startHeight, int endHeight, int tileset);
		void genFill(int x1, int y1, int x2, int y2, int tileset);


	public:
		void generate();
	};
}

#endif
