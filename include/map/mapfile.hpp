/***********************************************************************
     * File       : mapfile.hpp
     * Created    : Aug 27, 2013
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#ifndef __MAPFILE
#define __MAPFILE


#include "tile.hpp"
#include "objects.hpp"
#include "phys.hpp"
#include "world.hpp"

#include "mapfile_gensave.hpp"
#include "mapfile_mapsave.hpp"
#include "mapfile_mapload.hpp"


void mapLoad(fired::Map *map, const char* filename);
void mapSave(fired::Map *map, const char* filename);
void genSave(fired::MapGenerator *gen, const char* filename);

#endif
