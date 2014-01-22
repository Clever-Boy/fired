/***********************************************************************
     * File       : gen_biome_city.cpp
     * Created    : Jan 22, 2014
     * Copyright  : (C) 2013 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#include "game.hpp"



/***********************************************************************
     * MapGenerator
     * genCity

***********************************************************************/
void fired::MapGenerator::genCity() {
	genCityLandscape(0, sizeX - 1, 40);
	genCityDecors();
	genCityPlatforms();
	genCityCollectors();
	genCityPlayer();
}



/***********************************************************************
     * MapGenerator
     * genCityLandscape

***********************************************************************/
void fired::MapGenerator::genCityLandscape(int areaStart, int areaEnd, int horizon) {
	genFill(areaStart, horizon, areaEnd, sizeY - 1, 1, true);
	genFill(areaStart, horizon - 2, areaEnd, horizon - 1, 1, false);

	genFill(areaStart  , horizon - 2, areaStart + 3, horizon - 1, 1, true);
	genFill(areaEnd - 4, horizon - 2, areaEnd   - 1, horizon - 1, 1, true);

	genFill(areaStart + 4, horizon - 1, areaStart + 7, horizon - 1, 1, true);
	genFill(areaEnd - 8  , horizon - 1, areaEnd - 5  , horizon - 1, 1, true);

	//Generating testing planes
	genBar(41, horizon - 6, horizon - 1, 2, false);
	genBar(47, horizon - 6, horizon - 1, 2, false);
	genFill(41, horizon - 2, 47, horizon - 1, 2, false);
	genFill(40, horizon - 5, 48, horizon - 3, 4, true);

	genBar(81, horizon - 6, horizon - 1, 2, false);
	genBar(87, horizon - 6, horizon - 1, 2, false);
	genFill(81, horizon - 2, 87, horizon - 1, 2, false);
	genFill(80, horizon - 5, 88, horizon - 5, 4, true);

	//Generating testing house
	genFill(140, horizon - 10, 159, horizon - 1, 3, false);
	genFill(140, horizon, 159, horizon, 3, true);
	genFill(140, horizon - 10, 159, horizon - 9, 3, true);
	genBar(140, horizon - 10, horizon - 6, 3, true);
	genBar(159, horizon - 10, horizon - 6, 3, true);

	genFill(142, horizon - 11, 157, horizon - 11, 3, true);
	genFill(144, horizon - 12, 155, horizon - 12, 3, true);
	genFill(146, horizon - 13, 153, horizon - 13, 3, true);
	genFill(148, horizon - 14, 151, horizon - 14, 3, true);
}



/***********************************************************************
     * MapGenerator
     * genCityDecors

***********************************************************************/
void fired::MapGenerator::genCityDecors() {
	decors.push_back(new fired::MapDecor("box", sf::Vector2f(1900, 608)));
	decors.push_back(new fired::MapDecor("box", sf::Vector2f(1932, 608)));
	decors.push_back(new fired::MapDecor("box", sf::Vector2f(1916, 576)));

	decors.push_back(new fired::MapDecor("barrel", sf::Vector2f(2288, 608)));
	decors.push_back(new fired::MapDecor("barrel", sf::Vector2f(2368, 608)));
	decors.push_back(new fired::MapDecor("barrel", sf::Vector2f(2400, 608)));
}



/***********************************************************************
     * MapGenerator
     * genCityPlatforms

***********************************************************************/
void fired::MapGenerator::genCityPlatforms() {
	int x, y = 35;
	for (x = 49; x < 80; x++) {
		decors.push_back(new fired::MapDecor("bridge.metal", sf::Vector2f(x*TILE_SIZE, y*TILE_SIZE)));
		tiles[x][y].isPlatform = true;
	}
}



/***********************************************************************
     * MapGenerator
     * genCityCollectors

***********************************************************************/
void fired::MapGenerator::genCityCollectors() {
	objects.push_back(new fired::BaseMapObjectCollector("chest", sf::Vector2f(44*TILE_SIZE, 33*TILE_SIZE)));
	((fired::BaseMapObjectCollector*)objects.back())->generateLoot();

	objects.push_back(new fired::BaseMapObjectCollector("chest", sf::Vector2f(84*TILE_SIZE, 33*TILE_SIZE)));
	((fired::BaseMapObjectCollector*)objects.back())->generateLoot();
}



/***********************************************************************
     * MapGenerator
     * genCityPlayer

***********************************************************************/
void fired::MapGenerator::genCityPlayer() {
	int y = 0;
	startPos.x = (sizeX / 2) * TILE_SIZE;

	while (!tiles[sizeX / 2][y].tileset || !tiles[sizeX / 2][y].isWall) y++;
	startPos.y = (y - 3) * TILE_SIZE;
}
