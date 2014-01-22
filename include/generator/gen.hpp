/***********************************************************************
     * File       : generator.hpp
     * Created    : Jul 31, 2013
     * Copyright  : (C) 2013 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#ifndef __GEN
#define __GEN


namespace fired {
	struct MapGenerator {
		fired::MapTile **tiles;
		sf::Vector2f     startPos;
		int sizeX;
		int sizeY;

		std::vector<fired::MapDecor*> decors;
		std::vector<fired::BaseMapObject*> objects;

		void genLandscape(int areaStart, int areaEnd, int horizon);
		void genClear(int xSize, int ySize);
		void genPlayer();
		void genDecors();
		void genPlatforms();
		void genCollectors();

		void genBar(int x, int startHeight, int endHeight, int tileset, bool isWall);
		void genFill(int x1, int y1, int x2, int y2, int tileset, bool isWall);


		 MapGenerator();
		~MapGenerator();

		void generate();
	};
}

#endif
