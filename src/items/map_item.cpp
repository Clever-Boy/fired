/***********************************************************************
     * File       : map_item.cpp
     * Created    : Sep 03, 2013
     * Copyright  : (C) 2013 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#include "game.hpp"



/***********************************************************************
     * MapItem
     * constructor

***********************************************************************/
fired::MapItem::MapItem(unsigned int _count, const char *_name) {
	count = _count;
	strncpy(name, _name, sizeof(name));
}
