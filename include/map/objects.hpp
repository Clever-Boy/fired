#ifndef __OBJECTS
#define __OBJECTS


#include "decor.hpp"

namespace fired {
	enum MapObjectType {
		moNone,
		moCollector
	};



	struct BaseMapObject {
		char                 decorName[16];
		sf::Vector2f         pos;
		fired::MapObjectType type;


		BaseMapObject() {};
		BaseMapObject(const char *_name, sf::Vector2f _pos, fired::MapObjectType _type);
	};



	struct MapObject {
		fired::Decor        *decor;
		fired::MapObjectType type;


		 MapObject() {};
		 MapObject(fired::Decor *_decor);
		~MapObject();

		void render();
	};



	struct MapObjectCollector : MapObject {
		fired::InventoryItem *items[10][5];


		 MapObjectCollector(fired::Decor *_decor);
		~MapObjectCollector();
	};
}

#endif
