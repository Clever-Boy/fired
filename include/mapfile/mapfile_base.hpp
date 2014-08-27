/***********************************************************************
     * File       : mapfile_base.hpp
     * Created    : Aug 27, 2013
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#ifndef __MAPFILE_BASE
#define __MAPFILE_BASE


#include "map.hpp"
#include "mapfile_gensave.hpp"
#include "mapfile_genload.hpp"
#include "mapfile_mapsave.hpp"
#include "mapfile_mapload.hpp"


void mapLoad(fired::Map *map, const char* filename);
void mapSave(fired::Map *map, const char* filename);
void genLoad(fired::MapGenerator *gen, const char* filename);
void genSave(fired::MapGenerator *gen, const char* filename);

#endif
