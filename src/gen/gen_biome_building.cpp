/***********************************************************************
     * File       : gen_biome_building.cpp
     * Created    : Jan 22, 2014
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#include "game.hpp"



/***********************************************************************
     * MapGenerator
     * genBuilding

***********************************************************************/
void fired::MapGenerator::genBuilding() {
	genBuildingMeta();
	genBuildingPalette();
	genBuildingBase();
	genBuildingRooms();
	genBuildingDoors();
	genBuildingLadder();
	genBuildingPlayer();
}



/***********************************************************************
     * MapGenerator
     * genBuildingPalette

***********************************************************************/
void fired::MapGenerator::genBuildingPalette() {
	addTileToPalette("brick.red");
	addTileToPalette("brick.gray");
	addTileToPalette("concrete");
	addTileToPalette("warning");
}



/***********************************************************************
     * MapGenerator
     * genBuildingMeta

***********************************************************************/
void fired::MapGenerator::genBuildingMeta() {
	building.rooms.x = random() % 6 + 5;
	building.rooms.y = random() % 6 + 3;

	building.roomSize.x = random() % 20 + 30;
	building.roomSize.y = random() % 10 + 15;

	building.ladderPos = random() % (building.rooms.x + 1);
	building.ladder    = random() % 15 + 10;
	building.attic     = random() % 10 + 20;
	building.roof      = random() % 20 + 30;
	building.wall      = random() % 3  + 3;
	building.floor     = random() % 3  + 3;
	building.door      = random() % 4  + 5;

	sf::Vector2i size(0, 0);

	size.x += building.rooms.x * building.roomSize.x;
	size.x += building.ladder;
	size.x += building.wall * (building.rooms.x + 2);

	size.y += building.rooms.y * building.roomSize.y;
	size.y += building.floor * (building.rooms.y + 2);
	size.y += building.roof;
	size.y += building.attic;

	genClear(size.x, size.y);
}



/***********************************************************************
     * MapGenerator
     * genBuildingRooms

***********************************************************************/
void fired::MapGenerator::genBuildingBase() {
	setBrush("concrete");
	genFill(0, building.roof, sizeX - 1, sizeY - building.attic - 1, true);

	setBrush("brick.red");
	genFill(0, sizeY - building.attic, sizeX - 1, sizeY - 1, true);
}



/***********************************************************************
     * MapGenerator
     * genBuildingRooms

***********************************************************************/
void fired::MapGenerator::genBuildingRooms() {
	int roomX, roomY;

	roomX = building.wall;
	for (int i = 0; i < building.rooms.x; i++) {
		roomY = building.floor + building.roof;
		if (i == building.ladderPos) roomX += building.wall + building.ladder;

		for (int j = 0; j < building.rooms.y; j++) {
			genBuildingRoom(roomX, roomY);
			roomY += building.roomSize.y + building.floor;
		}

		roomX += building.roomSize.x + building.wall;
	}
}



/***********************************************************************
     * MapGenerator
     * genBuildingDoors

***********************************************************************/
void fired::MapGenerator::genBuildingDoors() {
	int roomY;

	setBrush("brick.gray");
	roomY = building.roof + building.floor + building.roomSize.y - building.door;

	for (int i = 0; i < building.rooms.y; i++) {
		genFill(building.wall, roomY, sizeX - building.wall - 1, roomY + building.door - 1, false);
		roomY += building.floor + building.roomSize.y;
	}
}



/***********************************************************************
     * MapGenerator
     * genBuildingRoom

***********************************************************************/
void fired::MapGenerator::genBuildingRoom(int x, int y) {
	setBrush("brick.gray");
	genFill(x, y, x + building.roomSize.x - 1, y + building.roomSize.y - 1, false);

	addLightSource((x + 1) * TILE_SIZE, (y + 1) * TILE_SIZE, "wall.lamp");
	addLightSource((x + building.roomSize.x - 2) * TILE_SIZE, (y + 1) * TILE_SIZE, "wall.lamp");
}



/***********************************************************************
     * MapGenerator
     * genBuildingLadder

***********************************************************************/
void fired::MapGenerator::genBuildingLadder() {
	int x1, y1, x2, y2;

	setBrush("brick.gray");

	x1 = (building.wall + building.roomSize.x) * building.ladderPos + building.wall;
	y1 = building.roof;

	x2 = (building.wall + building.roomSize.x) * building.ladderPos + building.wall + building.ladder;
	y2 = sizeY - building.attic - 1;

	genFill(x1, y1, x2, y2, false);
}



/***********************************************************************
     * MapGenerator
     * genBuildingPlayer

***********************************************************************/
void fired::MapGenerator::genBuildingPlayer() {
	startPos.x = 6 * TILE_SIZE;
	startPos.y = (building.roof + building.floor + building.roomSize.y - 3) * TILE_SIZE;
}
