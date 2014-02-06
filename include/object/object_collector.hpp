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


		BaseMapObjectCollector(unsigned int id, sf::Vector2f _pos);

		void generateLoot();
		void addItem(unsigned int _count, const char *name);
	};



	struct MapObjectCollector : MapObject {
		fired::InventoryItem items[10][5];

		MapObjectCollector(unsigned int _decorId, sf::Vector2f pos);
	};
}

#endif
