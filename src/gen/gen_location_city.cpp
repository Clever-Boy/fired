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
	for (int i = 0; i < 8; i++) genLocationCityHouse(sf::IntRect(5 + i * 25, 35, 24, 14));
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
void fired::MapGenerator::genLocationCityHouse(sf::IntRect rect) {
	int width = rect.width - 7 - rand() % (int)(rect.width * 0.3);
	int offset = 2 + rand() % (rect.width - width);

	int height = rect.height - rand() % (int)(rect.height * 0.3);
	int roofHeight = 3 + rand() % 4;
	int houseHeight = height - roofHeight;

	genLocationCitySetRandomBrick();
	genFillRect(sf::IntRect(rect.left + offset, rect.top + rect.height - houseHeight, width, houseHeight), false);

	genLocationCitySetRandomPlank();

	int roofOffset = (4 + width) / (2 * roofHeight) + 1;
	for (int i = 0; i < roofHeight; i++)
		genFillRect(sf::IntRect(rect.left + offset - 2 + roofOffset * i, rect.top + rect.height - houseHeight - i, width + 4 - 2 * roofOffset * i, 0), false);
}
