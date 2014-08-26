/***********************************************************************
     * File       : location_room.hpp
     * Created    : Aug 26, 2014
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#ifndef __LOCATION_ROOM
#define __LOCATION_ROOM


namespace fired {
	struct LocationHomeCraftingStations {
		sf::Vector2i pos;
		unsigned int id;
	};



	struct LocationHomeRoom {
		sf::IntRect rect;

		int floor;
		int position;
	};



	struct LocationHomeLivingRoom : LocationHomeRoom {
		unsigned int npc;

		bool furniture[3];
		bool picture;
	};



	struct LocationHomeTreasureRoom : LocationHomeRoom {
		bool improved;
	};



	struct LocationHomeCraftingRoom : LocationHomeRoom {
		bool exists;
		std::vector<fired::LocationHomeCraftingStations> stations;
	};



	struct LocationHomeStairsRoom : LocationHomeRoom {
		bool exists;
		unsigned int treasureFloors;
		unsigned int npcFloors;
	};



	struct LocationHomeBedRoomRoom : LocationHomeRoom {
		bool furniture[3];
		bool picture;
	};



	struct LocationHomeHallRoom : LocationHomeRoom {
		bool furniture[2];
		bool picture[2];
	};



	struct LocationHomeStructure {
		fired::LocationHomeBedRoomRoom  bedRoom;
		fired::LocationHomeHallRoom     hallRoom;
		fired::LocationHomeStairsRoom   stairsRoom;
		fired::LocationHomeCraftingRoom craftingRoom;

		std::vector<fired::LocationHomeTreasureRoom> treasureRooms;
		std::vector<fired::LocationHomeLivingRoom>   npcRooms;

		unsigned int brickTile;
		unsigned int wallTile;

		void defaults();
		void loadFromFile();
		void saveToFile();
	};
}

#endif
