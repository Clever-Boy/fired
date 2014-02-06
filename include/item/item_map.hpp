/***********************************************************************
     * File       : item_map.hpp
     * Created    : Sep 03, 2013
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#ifndef __ITEM_MAP
#define __ITEM_MAP


namespace fired {
	struct MapItem {
		int          id;
		unsigned int count;

		MapItem() {};
		MapItem(unsigned int _count, int _id);
	};
}

#endif
