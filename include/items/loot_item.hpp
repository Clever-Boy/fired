/***********************************************************************
     * File       : loot_item.hpp
     * Created    : Sep 03, 2013
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#ifndef __LOOT_ITEM
#define __LOOT_ITEM


namespace fired {
	struct LootItem {
		fired::BaseItem *base;

		unsigned int     minCount;
		unsigned int     maxCount;
		float            probability;


		LootItem(fired::BaseItem *_base, unsigned int _minCount, unsigned int _maxCount, float _probability);
	};
}

#endif
