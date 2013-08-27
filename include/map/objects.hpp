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



	struct BaseMapObjectCollector : BaseMapObject {
		std::vector<fired::MapItem*> items;


		BaseMapObjectCollector() {};
		BaseMapObjectCollector(const char *_name, sf::Vector2f _pos);

		void generateLoot();
		void addItem(fired::ItemType _type, unsigned int _count, const char *_name);
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
