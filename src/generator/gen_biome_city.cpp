/***********************************************************************
     * File       : gen_biome_city.cpp
     * Created    : Jan 22, 2014
     * Copyright  : (C) 2014 Achpile
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
	genFill(areaStart, horizon, areaEnd, sizeY - 1, biome->ground->ID, true);
	genFill(areaStart, horizon - 2, areaEnd, horizon - 1, biome->ground->ID, false);

	genFill(areaStart  , horizon - 2, areaStart + 3, horizon - 1, biome->ground->ID, true);
	genFill(areaEnd - 4, horizon - 2, areaEnd      , horizon - 1, biome->ground->ID, true);

	genFill(areaStart + 4, horizon - 1, areaStart + 7, horizon - 1, biome->ground->ID, true);
	genFill(areaEnd - 8  , horizon - 1, areaEnd - 5  , horizon - 1, biome->ground->ID, true);

	//Generating testing planes

	genBar(41, horizon - 11, horizon - 6, biome->brickSecond->ID, false);
	genBar(47, horizon - 11, horizon - 6, biome->brickSecond->ID, false);
	genFill(41, horizon - 7, 47, horizon - 6, biome->brickSecond->ID, false);
	genFill(40, horizon - 10, 48, horizon - 10, biome->extra->ID, true);

	genBar(81, horizon - 11, horizon - 6, biome->brickSecond->ID, false);
	genBar(87, horizon - 11, horizon - 6, biome->brickSecond->ID, false);
	genFill(81, horizon - 7, 87, horizon - 6, biome->brickSecond->ID, false);
	genFill(80, horizon - 10, 88, horizon - 10, biome->extra->ID, true);


	genFill(40, horizon - 5, 88, horizon - 5, biome->brickSecond->ID, true);
	genFill(40, horizon - 4, 88, horizon - 1, biome->brickSecond->ID, false);

	//Generating testing house
	genFill(140, horizon - 10, 159, horizon - 1, biome->brickMain->ID, false);
	genFill(140, horizon, 159, horizon, biome->brickMain->ID, true);
	genFill(140, horizon - 10, 159, horizon - 9, biome->brickMain->ID, true);
	genBar(140, horizon - 10, horizon - 6, biome->brickMain->ID, true);
	genBar(159, horizon - 10, horizon - 6, biome->brickMain->ID, true);

	genFill(142, horizon - 11, 157, horizon - 11, biome->brickMain->ID, true);
	genFill(144, horizon - 12, 155, horizon - 12, biome->brickMain->ID, true);
	genFill(146, horizon - 13, 153, horizon - 13, biome->brickMain->ID, true);
	genFill(148, horizon - 14, 151, horizon - 14, biome->brickMain->ID, true);

	//Generating one more testing house
	genFill(0, horizon - 8, 19, horizon-1, biome->brickMain->ID, false);
	genFill(0, horizon - 10, 1, horizon-1, biome->brickMain->ID, true);
	genFill(0, horizon - 10, 18, horizon - 10, biome->brickMain->ID, true);
	genFill(0, horizon - 9, 21, horizon - 9, biome->brickMain->ID, true);
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
	int x, y = 30;
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
