/***********************************************************************
     * File       : gen_biome_sewers.cpp
     * Created    : Apr 02, 2014
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#include "game.hpp"



/***********************************************************************
     * MapGenerator
     * genSewers

***********************************************************************/
void fired::MapGenerator::genSewers() {
	genSewersMeta();
	genSewersPalette();
	genSewersLandscape(0, sizeX - 1, 40);
	genSewersDecors();
	genSewersPlatforms();
	genSewersCollectors();
	genSewersPlayer();
	genSewersSpawns();
}



/***********************************************************************
     * MapGenerator
     * genSewersPalette

***********************************************************************/
void fired::MapGenerator::genSewersPalette() {
	addTileToPalette("brick.cobble");
	addTileToPalette("brick.sewer");
	addTileToPalette("stone.cobble");
	addTileToPalette("mud");
}



/***********************************************************************
     * MapGenerator
     * genSewersMeta

***********************************************************************/
void fired::MapGenerator::genSewersMeta() {
	genClear(200, 100);
}



/***********************************************************************
     * MapGenerator
     * genSewersLandscape

***********************************************************************/
void fired::MapGenerator::genSewersLandscape(int areaStart, int areaEnd, int horizon) {
	setBrush("stone.cobble");
	genFill(areaStart, horizon, areaEnd, sizeY - 1, true);
	genFill(areaStart, horizon - 2, areaEnd, horizon - 1, false);

	genFill(areaStart  , horizon - 2, areaStart + 3, horizon - 1, true);
	genFill(areaEnd - 4, horizon - 2, areaEnd      , horizon - 1, true);

	genFill(areaStart + 4, horizon - 1, areaStart + 7, horizon - 1, true);
	genFill(areaEnd - 8  , horizon - 1, areaEnd - 5  , horizon - 1, true);

	//Generating testing planes
	setBrush("brick.sewer");
	genBar(41, horizon - 11, horizon - 6, false);
	genBar(47, horizon - 11, horizon - 6, false);
	genFill(41, horizon - 7, 47, horizon - 6, false);

	genBar(81, horizon - 11, horizon - 6, false);
	genBar(87, horizon - 11, horizon - 6, false);
	genFill(81, horizon - 7, 87, horizon - 6, false);

	genFill(40, horizon - 5, 88, horizon - 5, true);
	genFill(40, horizon - 4, 88, horizon - 1, false);

	setBrush("mud");
	genFill(40, horizon - 10, 48, horizon - 10, true);
	genFill(80, horizon - 10, 88, horizon - 10, true);


	//Generating testing house
	setBrush("brick.cobble");
	genFill(140, horizon - 10, 159, horizon - 1, false);
	genFill(140, horizon, 159, horizon, true);
	genFill(140, horizon - 10, 159, horizon - 9, true);
	genBar(140, horizon - 10, horizon - 6, true);
	genBar(159, horizon - 10, horizon - 6, true);

	genFill(142, horizon - 11, 157, horizon - 11, true);
	genFill(144, horizon - 12, 155, horizon - 12, true);
	genFill(146, horizon - 13, 153, horizon - 13, true);
	genFill(148, horizon - 14, 151, horizon - 14, true);

	//Generating one more testing house
	genFill(0, horizon - 8, 19, horizon-1, false);
	genFill(0, horizon - 10, 1, horizon-1, true);
	genFill(0, horizon - 10, 18, horizon - 10, true);
	genFill(0, horizon - 9, 21, horizon - 9, true);


	//Generating cave
	setBrush("brick.sewer");
	genFill(62, horizon, 66, horizon + 25, false);
	genFill(42, horizon + 21, 86, horizon + 25, false);
}



/***********************************************************************
     * MapGenerator
     * genSewersDecors

***********************************************************************/
void fired::MapGenerator::genSewersDecors() {
	addDecor(119, 38, "box");
	addDecor(121, 38, "box");
	addDecor(120, 36, "box");

	addDecor(143, 38, "barrel");
	addDecor(148, 38, "barrel");
	addDecor(150, 38, "barrel");

	addLightSource(142, 33, "wall.lamp.red");
	addLightSource(157, 33, "wall.lamp.blue");

	addLightSource(43 , 62, "wall.lamp");
	addLightSource(85 , 62, "wall.lamp");
	addLightSource(64 , 57, "wall.lamp");
}



/***********************************************************************
     * MapGenerator
     * genSewersPlatforms

***********************************************************************/
void fired::MapGenerator::genSewersPlatforms() {
	for (int x = 49; x < 80; x++) addPlatform(x, 30, "bridge.metal");
	for (int x = 62; x < 67; x++) addPlatform(x, 40, "bridge.metal");
	for (int x = 62; x < 67; x++) addPlatform(x, 45, "bridge.metal");
	for (int x = 62; x < 67; x++) addPlatform(x, 50, "bridge.metal");
	for (int x = 62; x < 67; x++) addPlatform(x, 55, "bridge.metal");
	for (int x = 62; x < 67; x++) addPlatform(x, 60, "bridge.metal");
}



/***********************************************************************
     * MapGenerator
     * genSewersCollectors

***********************************************************************/
void fired::MapGenerator::genSewersCollectors() {
	addCollector(44, 33, "chest");
	addCollector(84, 33, "chest");
}



/***********************************************************************
     * MapGenerator
     * genSewersPlayer

***********************************************************************/
void fired::MapGenerator::genSewersPlayer() {
	setStart(sizeX / 2, 36, 10, 5);
}



/***********************************************************************
     * MapGenerator
     * genSewersSpawns

***********************************************************************/
void fired::MapGenerator::genSewersSpawns() {
	return;
}
