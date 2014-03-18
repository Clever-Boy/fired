/***********************************************************************
     * File       : gen_tileset.cpp
     * Created    : Mar 18, 2014
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#include "game.hpp"



/***********************************************************************
     * GenTileset
     * constructor

***********************************************************************/
fired::GenTileset::GenTileset(int _ID, const char *_name) {
	ID = _ID;
	strcpy(name, _name);
}
