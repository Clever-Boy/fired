/***********************************************************************
     * File       : map_item.hpp
     * Created    : Sep 03, 2013
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#ifndef __MAP_ITEM
#define __MAP_ITEM


namespace fired {
	struct MapItem {
		char            name[64];
		unsigned int    count;

		MapItem() {};
		MapItem(unsigned int _count, const char *_name);
	};
}

#endif
