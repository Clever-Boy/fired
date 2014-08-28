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
	addTeleport(99, 73, "door.wooden", ttCity);


	genFill(66, 69, 87, 76, true);
	genFill(67, 70, 86, 75, false);
	addLightSource(69, 70, "lantern");
	addLightSource(83, 70, "lantern");

	genFill(87, 71, 89, 76, true);
	genFill(87, 72, 89, 75, false);
}



/***********************************************************************
     * MapGenerator
     * genLocationHomePlayer

***********************************************************************/
void fired::MapGenerator::genLocationHomePlayer() {
	setStart(67, 70, 20, 6);
}
