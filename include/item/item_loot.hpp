/***********************************************************************
     * File       : item_loot.hpp
     * Created    : Sep 03, 2013
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#ifndef __ITEM_LOOT
#define __ITEM_LOOT


namespace fired {
	struct MapLootItem {
		std::vector<int> items;

		unsigned int     minCount;
		unsigned int     maxCount;
		float            probability;


		MapLootItem(const char *__items, unsigned int _minCount, unsigned int _maxCount, float _probability);
	};


	struct LootItem {
		std::vector<fired::BaseItem *> items;

		unsigned int     minCount;
		unsigned int     maxCount;
		float            probability;


		LootItem(unsigned int _minCount, unsigned int _maxCount, float _probability);

		void addItem(fired::BaseItem *item);
	};
}

#endif
