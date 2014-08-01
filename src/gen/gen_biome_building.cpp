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
	genBuildingCreateLoot();
	genBuildingBase();
	genBuildingRooms();
	genBuildingDoors();
	genBuildingLadder();
	genBuildingPlayer();
	genBuildingSpawns();
	genBuildingClearLoot();
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
	building.rooms.x = rand() % 6 + 5;
	building.rooms.y = rand() % 6 + 3;

	building.roomSize.x = rand() % 20 + 30;
	building.roomSize.y = rand() % 10 + 15;

	building.ladderPos = rand() % (building.rooms.x + 1);
	building.ladder    = rand() % 15 + 10;
	building.attic     = rand() % 10 + 20;
	building.roof      = rand() % 20 + 30;
	building.wall      = rand() % 3  + 3;
	building.floor     = rand() % 3  + 3;
	building.door      = rand() % 4  + 5;

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

	setEraser();
	int width = building.roomSize.x - 2 * building.wall - 1;

	int x1, y1, x2, y2;
	int sizeSide, sizeCenter, spacing;
	sizeSide = (width - 2 * building.wall) / 3;

	if (sizeSide * 3 == width - 2 * building.wall) sizeCenter = sizeSide;
	else                                           sizeCenter = width - 2 * building.wall - 2 * sizeSide;

	spacing = building.wall;

	y1 = y + building.wall;
	y2 = y1 + building.wall;

	if (y + building.roomSize.y - 1 - building.door - building.wall > y2)
		y2 = y + building.roomSize.y - 1 - building.door - building.wall;


	x1 = x + building.wall;
	x2 = x1 + sizeSide - 1;
	genFill(x1, y1, x2, y2, false);

	x1 = x2 + spacing + 1;
	x2 = x1 + sizeCenter - 1;
	genFill(x1, y1, x2, y2, false);

	x1 = x2 + spacing + 1;
	x2 = x1 + sizeSide - 1;
	genFill(x1, y1, x2, y2, false);
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

	x1 += 2;
	x2 -= 2;

	for (int i = 1; i <= building.rooms.y; i++) {
		y1 = building.roof + (building.roomSize.y + building.floor) * i - building.door - 2;

		addLightSource(x1, y1, "wall.lamp");
		addLightSource(x2, y1, "wall.lamp");
	}
}



/***********************************************************************
     * MapGenerator
     * genBuildingPlayer

***********************************************************************/
void fired::MapGenerator::genBuildingPlayer() {
	setStart(6, building.roof + building.floor + building.roomSize.y, 10, 3);
}



/***********************************************************************
     * MapGenerator
     * genBuildingSpawns

***********************************************************************/
void fired::MapGenerator::genBuildingSpawns() {
	return;
}



/***********************************************************************
     * MapGenerator
     * genBuildingCreateLoot

***********************************************************************/
void fired::MapGenerator::genBuildingCreateLoot() {
	return;
}



/***********************************************************************
     * MapGenerator
     * genBuildingClearLoot

***********************************************************************/
void fired::MapGenerator::genBuildingClearLoot() {
	return;
}
