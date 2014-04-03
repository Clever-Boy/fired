/***********************************************************************
     * File       : gen_biome_building.hpp
     * Created    : Jan 22, 2014
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#ifndef __GEN_BIOME_BUILDING
#define __GEN_BIOME_BUILDING


struct {
	sf::Vector2i rooms;
	sf::Vector2i roomSize;

	int          ladder;
	int          ladderPos;
	int          floor;
	int          wall;
	int          roof;
	int          attic;
	int          door;
} building;


void genBuilding();
void genBuildingMeta();
void genBuildingPalette();
void genBuildingBase();
void genBuildingRooms();
void genBuildingDoors();
void genBuildingLadder();
void genBuildingRoom(int x, int y);
void genBuildingPlayer();

#endif
