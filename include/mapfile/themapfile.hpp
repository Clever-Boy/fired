/***********************************************************************
     * File       : themapfile.hpp
     * Created    : Aug 27, 2013
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#ifndef __THEMAPFILE
#define __THEMAPFILE


#include "map.hpp"
#include "gensave.hpp"
#include "mapsave.hpp"
#include "mapload.hpp"


void mapLoad(fired::Map *map, const char* filename);
void mapSave(fired::Map *map, const char* filename);
void genSave(fired::MapGenerator *gen, const char* filename);

#endif
