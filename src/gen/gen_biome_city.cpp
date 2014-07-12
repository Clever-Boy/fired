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
	genFill(4, 76, 13, 81, false);
	genFill(7, 65, 10, 75, false);

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
		genFill(132 + i, 92 - i, 151 - i, 92 - i, true);

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
	genFill(166, 70, 197, 75, false);

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
	addDecor(119, 38, "box");
	addDecor(121, 38, "box");
	addDecor(120, 36, "box");

	addDecor(148, 38, "barrel");
	addDecor(150, 38, "barrel");

	addLightSource(142, 33, "wall.lamp.red");
	addLightSource(157, 33, "wall.lamp.blue");

	addLightSource(43 , 62, "wall.lamp");
	addLightSource(85 , 62, "wall.lamp");
	addLightSource(64 , 57, "wall.lamp");


	addLightSource(3 , 33, "wall.lamp.dim");

	addLightSource(5 , 62, "wall.lamp.dim");
	addLightSource(34, 62, "wall.lamp.dim");

	addLightSource(36, 50, "wall.lamp");
	addLightSource(49, 50, "wall.lamp");

	addLightSource(50, 79, "wall.lamp");
	addLightSource(78, 79, "wall.lamp");

	addLightSource(141, 45, "wall.lamp");
	addLightSource(158, 45, "wall.lamp");

	addLightSource(30 , 34, "lamp.post");
	addLightSource(114, 34, "lamp.post");
	addLightSource(125, 34, "lamp.post");
	addLightSource(183, 34, "lamp.post");

	addLightSource(119, 84, "wall.lamp");
	addLightSource(164, 84, "wall.lamp");

	addLightSource(119, 66, "lantern");
	addLightSource(134, 66, "lantern");
	addLightSource(149, 66, "lantern");
	addLightSource(164, 66, "lantern");

	addLightSource(184, 86, "wall.lamp.dim");
	addLightSource(196, 71, "wall.lamp");
	addLightSource(196, 55, "wall.lamp");

	addLightSource(27, 79, "wall.lamp.dim");
	addLightSource(34, 79, "wall.lamp.dim");

	addLightSource(95 , 50, "wall.lamp.dim");
	addLightSource(95 , 71, "wall.lamp.dim");
	addLightSource(114, 50, "wall.lamp.dim");
	addLightSource(125, 50, "wall.lamp.dim");

	// Central lab
	addDecor(142, 53, "metal.capsule");
	addDecor(158, 50, "bookcase");
	addDecor(158, 52, "bookcase");
	addDecor(158, 54, "bookcase");
	addDecor(156, 52, "bookcase");
	addDecor(156, 54, "bookcase");
	addDecor(153, 54, "shelf");
	addDecor(151, 52, "shelf.pc.off");
	addDecor(149, 52, "shelf.pc.on");
	addDecor(148, 54, "metal.chair");

	// Main lab
	addDecor(51, 82, "bookcase");
	addDecor(51, 84, "bookcase");
	addDecor(54, 84, "metal.chair");
	addDecor(55, 84, "metal.chair");
	addDecor(56, 84, "metal.chair");
	addDecor(58, 84, "shelf");
	addDecor(68, 84, "shelf");
	addDecor(68, 82, "bookcase");
	addDecor(66, 82, "shelf.pc.on");
	addDecor(70, 82, "shelf.pc.on");
	addDecor(72, 82, "shelf.pc.on");

	// Left lab
	addDecor(38, 55, "metal.capsule");
	addDecor(36, 54, "shelf.pc.off");
	addDecor(43, 55, "metal.capsule");
	addDecor(41, 54, "shelf.pc.off");
	addDecor(48, 55, "metal.capsule");
	addDecor(46, 54, "shelf.pc.off");

	// Seret room fake chests
	addDecor( 6, 80, "chest");
	addDecor( 8, 80, "chest");
	addDecor(10, 80, "chest");

	// Right lower room
	addDecor(181, 90, "metal.capsule");
	addDecor(179, 89, "shelf.pc.on");
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

	for (int x = 7 ; x < 11; x++) addPlatform(x, 66, "bridge.metal");
	for (int x = 7 ; x < 11; x++) addPlatform(x, 71, "bridge.metal");
	for (int x = 7 ; x < 11; x++) addPlatform(x, 76, "bridge.metal");

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
	for (int x =  47; x <  51; x++) addPlatform(x, 54, "bridge.wooden");
}



/***********************************************************************
     * MapGenerator
     * genCityCollectors

***********************************************************************/
void fired::MapGenerator::genCityCollectors() {
	addCollector( 44, 33, "chest");
	addCollector( 84, 33, "chest");
	addCollector(143, 38, "barrel");
	addCollector( 47, 52, "box");
	addCollector( 49, 52, "box");
	addCollector(  4, 80, "chest");
	addCollector( 12, 80, "chest");
	addCollector( 26, 81, "metal.capsule");
	addCollector(198, 32, "chest");
	addCollector(158, 48, "chest");
	addCollector(196, 58, "box");
	addCollector(196, 74, "box");
	addCollector(184, 91, "barrel");
	addCollector(141, 86, "chest");
}



/***********************************************************************
     * MapGenerator
     * genCityPlayer

***********************************************************************/
void fired::MapGenerator::genCityPlayer() {
	startPos.x = 170 * TILE_SIZE;
	startPos.y =  37 * TILE_SIZE;
}



/***********************************************************************
     * MapGenerator
     * genCitySpawns

***********************************************************************/
void fired::MapGenerator::genCitySpawns() {
	// Commented for debugging
	// addSpawn(141, 34, 16,  5);
	// addSpawn(  3, 34, 16,  5);
	// addSpawn( 55, 30, 19,  5);
	// addSpawn( 35, 49, 16, 23);
	// addSpawn(  4, 61, 32,  5);
	// addSpawn( 35, 80,  8,  5);
	// addSpawn( 42, 61, 45,  5);
	// addSpawn(140, 44, 20, 12);
	// addSpawn( 84, 49,  9,  7);
	// addSpawn(187, 55, 10,  5);
	// addSpawn(187, 71, 10,  5);
	// addSpawn(178, 85,  8,  6);
	// addSpawn(136, 76, 12,  7);
	// addSpawn(118, 85, 15,  8);
	// addSpawn(151, 85, 15,  8);
}
