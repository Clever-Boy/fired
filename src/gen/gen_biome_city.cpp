/***********************************************************************
     * File       : gen_biome_city.cpp
     * Created    : Apr 02, 2014
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
	genCityMeta();
	genCityPalette();
	genCityLandscape();
	genCityDecors();
	genCityPlatforms();
	genCityCollectors();
	genCityPlayer();
	genCitySpawns();
}



/***********************************************************************
     * MapGenerator
     * genCityPalette

***********************************************************************/
void fired::MapGenerator::genCityPalette() {
	addTileToPalette("brick.brown");
	addTileToPalette("brick.clay.silver");
	addTileToPalette("plate");
	addTileToPalette("plank.dark");
}



/***********************************************************************
     * MapGenerator
     * genCityMeta

***********************************************************************/
void fired::MapGenerator::genCityMeta() {
	genClear(200, 100);
}



/***********************************************************************
     * MapGenerator
     * genCityLandscape

***********************************************************************/
void fired::MapGenerator::genCityLandscape() {
	setBrush("plate");
	genFill(0, 40, 199, 99, true);
	genFill(0, 38, 199, 39, false);

	genFill(0  , 38, 3  , 39, true);
	genFill(195, 38, 199, 39, true);

	genFill(4  , 39, 7  , 39, true);
	genFill(191, 39, 194, 39, true);

	//Generating testing planes
	setBrush("brick.clay.silver");
	genBar (41, 29, 34, false);
	genBar (47, 29, 34, false);
	genFill(41, 33, 47, 34, false);

	genBar (81, 29, 34, false);
	genBar (87, 29, 34, false);
	genFill(81, 43, 87, 34, false);

	genFill(40, 35, 88, 35, true);
	genFill(40, 36, 88, 39, false);

	setBrush("plank.dark");
	genFill(40, 30, 48, 30, true);
	genFill(80, 30, 88, 30, true);


	//Generating testing house
	setBrush("brick.brown");
	genFill(140, 30, 159, 39, false);
	genFill(140, 40, 159, 40, true);
	genFill(140, 30, 159, 31, true);
	genBar(140, 30, 34, true);
	genBar(159, 30, 34, true);

	genFill(142, 29, 157, 29, true);
	genFill(144, 28, 155, 28, true);
	genFill(146, 27, 153, 27, true);
	genFill(148, 26, 151, 26, true);

	//Generating one more testing house
	genFill(0, 32, 19, 39, false);
	genFill(0, 30, 1 , 39, true);
	genFill(0, 30, 18, 30, true);
	genFill(0, 31, 21, 31, true);


	//Generating cave
	setBrush("brick.clay.silver");
	genFill(62, 40, 66, 65, false);
	genFill(42, 61, 86, 65, false);

	//Generating left tunnel
	genFill(4, 40, 9, 55, false);

	for (int i = 1; i <= 5; i++)
		genFill(4 + i, 50 + i, 9 + i, 50 + i, false);

	for (int i = 1; i <= 10; i++)
		genFill(4 + i, 55 + i, 14 + i, 55 + i, false);

	genFill(4, 61, 35, 65, false);
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

	addLightSource(2272, 528, "wall.lamp.red");
	addLightSource(2512, 528, "wall.lamp.blue");

	addLightSource(688, 992, "wall.lamp");
	addLightSource(1360, 992, "wall.lamp");
	addLightSource(1024, 912, "wall.lamp");

	addLightSource(48, 512, "wall.lamp");

	addLightSource(80 , 992, "wall.lamp");
	addLightSource(544, 992, "wall.lamp");
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

	for (int x = 4 ; x < 10; x++) addPlatform(x, 40, "bridge.metal");
	for (int x = 4 ; x < 10; x++) addPlatform(x, 45, "bridge.metal");
	for (int x = 4 ; x < 10; x++) addPlatform(x, 50, "bridge.metal");

	for (int x = 4 ; x < 15; x++) addPlatform(x, 55, "bridge.metal");
	for (int x = 9 ; x < 20; x++) addPlatform(x, 61, "bridge.metal");
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
	startPos.x = (6) * TILE_SIZE;

	while (!tiles[sizeX / 2][y].tileset || !tiles[sizeX / 2][y].isWall) y++;
	startPos.y = (y - 3) * TILE_SIZE;
}



/***********************************************************************
     * MapGenerator
     * genCitySpawns

***********************************************************************/
void fired::MapGenerator::genCitySpawns() {
	// Commented for debugging
	// spawns.push_back(sf::IntRect(141*TILE_SIZE, 34*TILE_SIZE, 16*TILE_SIZE, 5*TILE_SIZE));
	// spawns.push_back(sf::IntRect(  3*TILE_SIZE, 34*TILE_SIZE, 16*TILE_SIZE, 5*TILE_SIZE));
}
