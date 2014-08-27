/***********************************************************************
     * File       : mapfile_genload.hpp
     * Created    : Aug 27, 2014
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#ifndef __MAPFILE_GENLOAD
#define __MAPFILE_GENLOAD

#include "gen.hpp"


void genLoadMeta(fired::MapGenerator *gen, FILE *fp);
void genLoadTiles(fired::MapGenerator *gen, FILE *fp);
void genLoadCollectorItems(fired::BaseMapObjectCollector *obj, FILE *fp);
void genLoadObject(fired::MapGenerator *gen, fired::BaseMapObject obj, FILE *fp);
void genLoadObjects(fired::MapGenerator *gen, FILE *fp);
void genLoadSpawns(fired::MapGenerator *gen, FILE *fp);

#endif
