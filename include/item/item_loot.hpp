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
	struct LootItem {
		fired::BaseItem *base;

		unsigned int     minCount;
		unsigned int     maxCount;
		float            probability;


		LootItem(fired::BaseItem *_base, unsigned int _minCount, unsigned int _maxCount, float _probability);
	};
}

#endif
