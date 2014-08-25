/***********************************************************************
     * File       : gen_location_city.cpp
     * Created    : Aug 20, 2014
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#include "game.hpp"



/***********************************************************************
     * MapGenerator
     * genLocationCity

***********************************************************************/
void fired::MapGenerator::genLocationCity() {
	genLocationCityMeta();
	genLocationCityPalette();
	genLocationCityLandscape();
	genLocationCityHouses();
	genLocationCityPlayer();
}



/***********************************************************************
     * MapGenerator
     * genLocationCityPalette

***********************************************************************/
void fired::MapGenerator::genLocationCityPalette() {
	addTileToPalette("grass");
	addTileToPalette("dirt");

	addTileToPalette("brick.snow");
	addTileToPalette("brick.brown");
	addTileToPalette("brick.gray");
	addTileToPalette("brick.red");
	addTileToPalette("brick.old");
	addTileToPalette("brick.stone");
	addTileToPalette("brick.cobble");
	addTileToPalette("brick.clay.gray");
	addTileToPalette("brick.clay.pink");
	addTileToPalette("brick.clay.silver");
	addTileToPalette("brick.clay.white");

	addTileToPalette("plank");
	addTileToPalette("plank.dark");
}



/***********************************************************************
     * MapGenerator
     * genLocationCityMeta

***********************************************************************/
void fired::MapGenerator::genLocationCityMeta() {
	genClear(210, 100);
}



/***********************************************************************
     * MapGenerator
     * genLocationCityLandscape

***********************************************************************/
void fired::MapGenerator::genLocationCityLandscape() {
	setBrush("grass");
	genFill(0, 50, 209, 99, true);
}



/***********************************************************************
     * MapGenerator
     * genLocationCityHouses

***********************************************************************/
void fired::MapGenerator::genLocationCityHouses() {
	int offset = 0;
	while (offset < 210)
		offset += genLocationCityHouse(50, offset, 210 - offset);
}



/***********************************************************************
     * MapGenerator
     * genLocationCityPlayer

***********************************************************************/
void fired::MapGenerator::genLocationCityPlayer() {
	setStart(170, 45, 8, 5);
}



/***********************************************************************
     * MapGenerator
     * genLocationCitySetRandomBrick

***********************************************************************/
void fired::MapGenerator::genLocationCitySetRandomBrick() {
	switch (rand() % 11) {
		case  0: setBrush("brick.snow"       ); break;
		case  1: setBrush("brick.brown"      ); break;
		case  2: setBrush("brick.gray"       ); break;
		case  3: setBrush("brick.red"        ); break;
		case  4: setBrush("brick.old"        ); break;
		case  5: setBrush("brick.stone"      ); break;
		case  6: setBrush("brick.cobble"     ); break;
		case  7: setBrush("brick.clay.gray"  ); break;
		case  8: setBrush("brick.clay.pink"  ); break;
		case  9: setBrush("brick.clay.silver"); break;
		case 10: setBrush("brick.clay.white" ); break;
	}
}



/***********************************************************************
     * MapGenerator
     * genLocationCitySetRandomPlank

***********************************************************************/
void fired::MapGenerator::genLocationCitySetRandomPlank() {
	switch (rand() % 2) {
		case  0: setBrush("plank"     ); break;
		case  1: setBrush("plank.dark"); break;
	}
}



/***********************************************************************
     * MapGenerator
     * genLocationCityHouse

***********************************************************************/
int fired::MapGenerator::genLocationCityHouse(int height, int offset, int left) {
	if (left < 18) return left;

	int startOffset = 4 + rand() % 4;
	int endOffset   = 4 + rand() % 4;

	int houseHeight = 6 + rand() % 6;
	int windowCount = 3 + rand() % 3;
	int windowOffset = 1 + rand() % 3;
	int width = 2 * windowCount + windowOffset * (windowCount + 1);
	int roofHeight = 3 + rand() % 4;

	int iteration = 0;
	while (width + startOffset + 2 > left) {
		switch (iteration) {
			case 0: startOffset  = 4; break;
			case 1: windowOffset = 1; break;
			case 2: windowCount  = 3; break;
			case 3: return left;
		}

		width = 2 * windowCount + windowOffset * (windowCount + 1);
		iteration++;
	}


	genLocationCitySetRandomBrick();
	genFillRect(sf::IntRect(offset + startOffset, height - houseHeight, width - 1, houseHeight - 1), false);

	genLocationCitySetRandomPlank();

	int roofOffset = (4 + width) / (2 * roofHeight) + 1;
	for (int i = 0; i < roofHeight; i++)
		genFillRect(sf::IntRect(offset + startOffset - 2 + roofOffset * i, height - houseHeight - i, width + 3 - 2 * roofOffset * i, 0), false);

	int doorIndex = rand() % windowCount;
	int windowTop = houseHeight / 2;
	bool twoWindows = false;

	if (houseHeight >= 10) {
		twoWindows = true;
		windowTop = houseHeight / 3;
	}

	for (int i = 0; i < windowCount; i++)
		if (twoWindows) {
			if (i == doorIndex) addDecor(offset + startOffset + 2 * i + windowOffset * (i + 1), height - 3                      , "door.wooden");
			else                addDecor(offset + startOffset + 2 * i + windowOffset * (i + 1), height - houseHeight + 2 * windowTop, "window.wooden");
			addDecor(offset + startOffset + 2 * i + windowOffset * (i + 1), height - houseHeight + windowTop, "window.wooden");
		} else {
			if (i == doorIndex) addDecor(offset + startOffset + 2 * i + windowOffset * (i + 1), height - 3                      , "door.wooden");
			else                addDecor(offset + startOffset + 2 * i + windowOffset * (i + 1), height - houseHeight + windowTop, "window.wooden");
		}

	return startOffset + width + endOffset;
}
