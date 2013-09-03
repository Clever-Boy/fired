#ifndef __COLLECTOR
#define __COLLECTOR

#include "map_objects.hpp"


namespace fired {
	struct BaseMapObjectCollector : BaseMapObject {
		std::vector<fired::MapItem*> items;


		BaseMapObjectCollector() {};
		BaseMapObjectCollector(const char *_name, sf::Vector2f _pos);

		void generateLoot();
		void addItem(fired::ItemType _type, unsigned int _count, const char *_name);
	};



	struct MapObjectCollector : MapObject {
		fired::InventoryItem *items[10][5];


		 MapObjectCollector(fired::Decor *_decor);
		~MapObjectCollector();
	};
}

#endif
