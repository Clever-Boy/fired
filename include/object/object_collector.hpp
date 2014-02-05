/***********************************************************************
     * File       : object_collector.hpp
     * Created    : Sep 03, 2013
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#ifndef __OBJECT_COLLECTOR
#define __OBJECT_COLLECTOR

#include "object_base.hpp"


namespace fired {
	struct BaseMapObjectCollector : BaseMapObject {
		std::vector<fired::MapItem*> items;


		BaseMapObjectCollector(const char *_name, sf::Vector2f _pos);

		void generateLoot();
		void addItem(unsigned int _count, const char *_name);
	};



	struct MapObjectCollector : MapObject {
		fired::InventoryItem items[10][5];

		MapObjectCollector(fired::Decor *_decor);
	};
}

#endif
