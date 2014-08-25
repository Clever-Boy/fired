/***********************************************************************
     * File       : gen_location_home.cpp
     * Created    : Aug 20, 2014
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#include "game.hpp"



/***********************************************************************
     * MapGenerator
     * genLocationHome

***********************************************************************/
void fired::MapGenerator::genLocationHome() {
	genLocationHomeMeta();
	genLocationHomePalette();
	genLocationHomeHall();
	genLocationHomePlayer();
}



/***********************************************************************
     * MapGenerator
     * genLocationHomePalette

***********************************************************************/
void fired::MapGenerator::genLocationHomePalette() {
	addTileToPalette("brick.mossy");
}



/***********************************************************************
     * MapGenerator
     * genLocationHomeMeta

***********************************************************************/
void fired::MapGenerator::genLocationHomeMeta() {
	genClear(200, 100);
}



/***********************************************************************
     * MapGenerator
     * genLocationHomeLandscape

***********************************************************************/
void fired::MapGenerator::genLocationHomeHall() {
	setBrush("brick.mossy");
	genFill(89, 69, 110, 76, true);
	genFill(90, 70, 109, 75, false);

	addLightSource( 93, 70, "lantern");
	addLightSource(106, 70, "lantern");

	addDecor(99, 73, "door.wooden");
}



/***********************************************************************
     * MapGenerator
     * genLocationHomePlayer

***********************************************************************/
void fired::MapGenerator::genLocationHomePlayer() {
	setStart(99, 73, 2, 3);
}
