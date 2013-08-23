#ifndef __GENERATOR
#define __GENERATOR


#include "tile.hpp"
#include "decor.hpp"


namespace fired {
	class MapGenerator {
	private:
		fired::MapTile **tiles;
		sf::Vector2f     startPos;
		int sizeX;
		int sizeY;

		std::vector<fired::MapDecor*> decors;

		void save(const char* filename);

		void genLandscape(int areaStart, int areaEnd, int horizon);
		void genClear(int xSize, int ySize);
		void genPlayer();
		void genDecors();

		void genBar(int x, int startHeight, int endHeight, int tileset, bool isWall);
		void genFill(int x1, int y1, int x2, int y2, int tileset, bool isWall);


	public:
		 MapGenerator();
		~MapGenerator();

		void generate();
	};
}

#endif
