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
	addTileToPalette("plank");
	addTileToPalette("dirt");
	addTileToPalette("dirt.hard");
	addTileToPalette("brick.clay.white");
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
	genFill(4, 61, 35, 65, false);

	for (int i = 1; i <=  5; i++) genFill(4 + i, 50 + i, 9  + i, 50 + i, false);
	for (int i = 1; i <= 10; i++) genFill(4 + i, 55 + i, 14 + i, 55 + i, false);

	//Generating left room
	genFill(16, 54, 50, 57, false);
	genFill(16, 54, 19, 59, false);

	setBrush("brick.clay.white");
	genFill(35, 49, 50, 57, false);

	setBrush("plate");
	genFill(16, 54, 16, 54, true);
	setBrush("brick.clay.silver");

	//Generating left secret room
	genFill(4, 76, 14, 81, false);
	genFill(7, 65, 11, 75, false);

	//Generating tunnels to main tunnel
	genFill(29, 66, 32, 77, false);
	genFill(45, 66, 48, 77, false);

	//Generating big tunnel
	genFill(26, 78, 96, 85, false);

	setBrush("plate");
	genFill(26, 84, 32, 84, true);
	genFill(26, 85, 34, 85, true);

	genFill(45, 84, 48, 84, true);
	genFill(43, 85, 50, 85, true);

	genFill(80, 84, 83, 84, true);
	genFill(78, 85, 85, 85, true);
	setBrush("brick.clay.silver");

	//Generating downstairs
	for (int i = 0; i <= 2; i++) genFill(94 + i, 85 + i, 96    , 85 + i, false);
	for (int i = 1; i <= 5; i++) genFill(96 + i, 78 + i, 96 + i, 87 + i, false);

	//Generating left lower enterance
	genFill(102, 83, 117, 92, false);

	//Generating large hall
	setBrush("plank");
	genFill(118, 66, 165, 92, false);

	setBrush("plate");
	for (int i = 0; i < 5; i++)
		genFill(132 + i, 92 - i, 152 - i, 92 - i, true);

	for (int i = 0; i < 7; i++) {
		genFill(118    , 76 + i, 118 + i, 76 + i, true);
		genFill(165 - i, 76 + i, 165    , 76 + i, true);
	}

	genFill(114, 82, 117, 88, true);
	setBrush("brick.clay.silver");
	genFill(102, 83, 113, 88, false);

	//Generating windows
	setEraser();
	genFill(121, 69, 132, 74, false);
	genFill(136, 69, 147, 74, false);
	genFill(151, 69, 162, 74, false);

	//Generating right lower room
	setBrush("brick.clay.silver");
	genFill(166, 89, 185, 92, false);
	genFill(178, 85, 185, 92, false);

	//Generating right tunnel
	genFill(174, 40, 179, 50, false);
	genFill(180, 54, 197, 59, false);
	genFill(174, 64, 181, 64, false);

	for (int i = 1; i <= 6; i++) genFill(179    , 47 + i, 179 + i, 47 + i, false);
	for (int i = 1; i <= 6; i++) genFill(179    , 65 - i, 180 + i, 65 - i, false);
	for (int i = 0; i <  6; i++) genFill(174 + i, 50 + i, 181    , 50 + i, false);
	for (int i = 1; i <= 7; i++) genFill(181 - i, 56 + i, 181    , 56 + i, false);

	//Generating right upper enterance
	genFill(174, 65, 180, 69, false);
	genFill(166, 70, 196, 75, false);

	//Generating left upper enterance
	genFill(93, 70, 117, 75, false);

	//Generating central tunnel
	genFill(80 , 56, 83 , 77, false);
	genFill(93 , 56, 97 , 69, false);
	genFill(80 , 49, 159, 55, false);
	genFill(116, 40, 123, 48, false);

	setBrush("plate");
	genFill(116, 55, 123, 55, true);
	genFill(118, 54, 121, 54, true);

	//Generating central lab
	setBrush("brick.clay.white");
	genFill(140, 44, 159, 55, false);

	//Generating right hill
	setBrush("dirt");
	genFill(185, 39, 199, 40, true);
	genFill(186, 37, 199, 38, true);
	genFill(187, 36, 199, 36, true);
	genFill(189, 35, 199, 35, true);
	genFill(195, 34, 199, 34, true);

	//Left dirt
	setBrush("dirt.hard");
	genFill(19, 30, 20, 30, true);
	genFill(0 , 29, 20, 29, true);
	genFill(0 , 28, 19, 28, true);
	genFill(0 , 27, 15, 27, true);
	genFill(0 , 26, 10, 26, true);
	genFill(0 , 25,  4, 25, true);

	//Generating main lab
	setBrush("brick.clay.white");
	genFill(49, 78, 79, 84, false);
	genFill(51, 85, 77, 85, false);
}



/***********************************************************************
     * MapGenerator
     * genCityDecors

***********************************************************************/
void fired::MapGenerator::genCityDecors() {
	addDecor(1740, 608, "box");
	addDecor(1772, 608, "box");
	addDecor(1756, 576, "box");

	addDecor(2288, 608, "barrel");
	addDecor(2368, 608, "barrel");
	addDecor(2400, 608, "barrel");

	addLightSource(2272, 528, "wall.lamp.red");
	addLightSource(2512, 528, "wall.lamp.blue");

	addLightSource(688, 992, "wall.lamp.dim");
	addLightSource(1360, 992, "wall.lamp.dim");
	addLightSource(1024, 912, "wall.lamp.dim");

	addLightSource(48, 528, "wall.lamp.dim");

	addLightSource(80 , 992, "wall.lamp.dim");
	addLightSource(544, 992, "wall.lamp.dim");

	addLightSource(576, 800, "wall.lamp");
	addLightSource(784, 800, "wall.lamp");

	addLightSource(800 , 1264, "wall.lamp");
	addLightSource(1248, 1264, "wall.lamp");

	addLightSource(2256, 720, "wall.lamp");
	addLightSource(2528, 720, "wall.lamp");

	addLightSource(480 , 544, "lamp.post");
	addLightSource(1824, 544, "lamp.post");
	addLightSource(2000, 544, "lamp.post");
	addLightSource(2928, 544, "lamp.post");

	addLightSource(1904, 1344, "wall.lamp");
	addLightSource(2624, 1344, "wall.lamp");

	addLightSource(1904, 1056, "lantern");
	addLightSource(2144, 1056, "lantern");
	addLightSource(2384, 1056, "lantern");
	addLightSource(2624, 1056, "lantern");
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
	for (int x = 62; x < 67; x++) addPlatform(x, 61, "bridge.metal");

	for (int x = 4 ; x < 10; x++) addPlatform(x, 40, "bridge.metal");
	for (int x = 4 ; x < 10; x++) addPlatform(x, 45, "bridge.metal");
	for (int x = 4 ; x < 10; x++) addPlatform(x, 50, "bridge.metal");

	for (int x = 4 ; x < 15; x++) addPlatform(x, 55, "bridge.metal");
	for (int x = 9 ; x < 20; x++) addPlatform(x, 61, "bridge.metal");

	for (int x = 7 ; x < 12; x++) addPlatform(x, 66, "bridge.metal");
	for (int x = 7 ; x < 12; x++) addPlatform(x, 71, "bridge.metal");
	for (int x = 7 ; x < 12; x++) addPlatform(x, 76, "bridge.metal");

	for (int x = 29; x < 33; x++) addPlatform(x, 66, "bridge.metal");
	for (int x = 29; x < 33; x++) addPlatform(x, 72, "bridge.metal");
	for (int x = 29; x < 33; x++) addPlatform(x, 78, "bridge.metal");

	for (int x = 45; x < 49; x++) addPlatform(x, 66, "bridge.metal");
	for (int x = 45; x < 49; x++) addPlatform(x, 72, "bridge.metal");
	for (int x = 45; x < 49; x++) addPlatform(x, 78, "bridge.metal");

	for (int x = 80; x < 84; x++) addPlatform(x, 56, "bridge.metal");
	for (int x = 80; x < 84; x++) addPlatform(x, 61, "bridge.metal");
	for (int x = 80; x < 84; x++) addPlatform(x, 66, "bridge.metal");
	for (int x = 80; x < 84; x++) addPlatform(x, 72, "bridge.metal");
	for (int x = 80; x < 84; x++) addPlatform(x, 78, "bridge.metal");

	for (int x = 93; x < 98; x++) addPlatform(x, 56, "bridge.metal");
	for (int x = 93; x < 98; x++) addPlatform(x, 61, "bridge.metal");
	for (int x = 93; x < 98; x++) addPlatform(x, 66, "bridge.metal");
	for (int x = 93; x < 98; x++) addPlatform(x, 70, "bridge.metal");

	for (int x = 116; x < 124; x++) addPlatform(x, 40, "bridge.metal");
	for (int x = 116; x < 124; x++) addPlatform(x, 44, "bridge.metal");
	for (int x = 116; x < 124; x++) addPlatform(x, 49, "bridge.metal");

	for (int x = 174; x < 180; x++) addPlatform(x, 40, "bridge.metal");
	for (int x = 174; x < 180; x++) addPlatform(x, 44, "bridge.metal");
	for (int x = 174; x < 181; x++) addPlatform(x, 48, "bridge.metal");
	for (int x = 174; x < 181; x++) addPlatform(x, 70, "bridge.metal");

	for (int x = 118; x < 166; x++) addPlatform(x, 83, "bridge.metal");
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
	int y = 40;
	startPos.x = (170) * TILE_SIZE;

	//while (!tiles[130][y].tileset || !tiles[130][y].isWall) y++;
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
