/***********************************************************************
     * File       : location_room.cpp
     * Created    : Aug 26, 2014
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#include "game.hpp"



/***********************************************************************
     * LocationHomeStructure
     * defaults

***********************************************************************/
void fired::LocationHomeStructure::defaults() {
	hallRoom.rect         = sf::IntRect(90, 70, 20, 6);
	hallRoom.floor        = 0;
	hallRoom.position     = -1;
	hallRoom.furniture[0] = false;
	hallRoom.furniture[1] = false;
	hallRoom.picture[0]   = false;
	hallRoom.picture[1]   = false;

	bedRoom.rect         = sf::IntRect(90, 70, 20, 6);
	bedRoom.floor        = 0;
	bedRoom.position     = -1;
	bedRoom.furniture[0] = false;
	bedRoom.furniture[1] = false;
	bedRoom.furniture[2] = false;
	bedRoom.picture      = false;

	craftingRoom.exists = false;
	craftingRoom.stations.clear();

	stairsRoom.exists         = false;
	stairsRoom.treasureFloors = 0;
	stairsRoom.npcFloors      = 0;

	treasureRooms.clear();
	npcRooms.clear();
}



/***********************************************************************
     * LocationHomeStructure
     * loadFromFile

***********************************************************************/
void fired::LocationHomeStructure::loadFromFile() {
	
}



/***********************************************************************
     * LocationHomeStructure
     * saveToFile

***********************************************************************/
void fired::LocationHomeStructure::saveToFile() {
	
}
