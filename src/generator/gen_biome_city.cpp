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
	genFill(areaStart, horizon, areaEnd, sizeY - 1, biome->brickSecond->ID, true);
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

	//Generating cave
	genFill(62, horizon, 66, horizon + 25, biome->brickSecond->ID, false);
	genFill(42, horizon + 21, 86, horizon + 25, biome->brickSecond->ID, false);
}



/***********************************************************************
     * MapGenerator
     * genCityDecors

***********************************************************************/
void fired::MapGenerator::genCityDecors() {
	addDecor(1900, 608, "box");
	addDecor(1932, 608, "box");
	addDecor(1916, 576, "box");

	addDecor(2288, 608, "barrel");
	addDecor(2368, 608, "barrel");
	addDecor(2400, 608, "barrel");

	addLightSource(2272, 528, "wall.lamp");
	addLightSource(2512, 528, "wall.lamp");

	addLightSource(688, 992, "wall.lamp");
	addLightSource(1360, 992, "wall.lamp");
	addLightSource(1024, 912, "wall.lamp");
}



/***********************************************************************
     * MapGenerator
     * genCityPlatforms

***********************************************************************/
void fired::MapGenerator::genCityPlatforms() {
	for (int x = 49; x < 80; x++) addPlatform(x, 30, "bridge.metal");
	for (int x = 62; x < 67; x++) addPlatform(x, 40, "bridge.metal");
	for (int x = 62; x < 67; x++) addPlatform(x, 45, "bridge.metal");
	for (int x = 62; x < 67; x++) addPlatform(x, 50, "bridge.metal");
	for (int x = 62; x < 67; x++) addPlatform(x, 55, "bridge.metal");
	for (int x = 62; x < 67; x++) addPlatform(x, 60, "bridge.metal");
}



/***********************************************************************
     * MapGenerator
     * genCityCollectors

***********************************************************************/
void fired::MapGenerator::genCityCollectors() {
	addCollector(704 , 528, "chest");
	addCollector(1344, 528, "chest");
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
