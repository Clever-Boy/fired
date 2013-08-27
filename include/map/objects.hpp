#ifndef __OBJECTS
#define __OBJECTS


#include "decor.hpp"

namespace fired {
	enum MapObjectType {
		moNone,
		moCollector
	};


/*
	struct BaseMapObject {
		char                 decorName[16];
		sf::Vector2f         pos;
		fired::MapObjectType type;


		MapObject() {};
		MapObject(const char *_name, sf::Vector2f _pos);
	};
*/


	struct MapObject {
		fired::Decor        *decor;
		sf::Vector2f         pos;
		fired::MapObjectType type;


		MapObject();
		void render();
	};



	struct MapObjectCollector : MapObject {
		fired::InventoryItem *items[10][5];


		 MapObjectCollector();
		~MapObjectCollector();
	};
}

#endif
