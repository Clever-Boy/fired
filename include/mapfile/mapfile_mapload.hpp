/***********************************************************************
     * File       : mapfile_mapload.hpp
     * Created    : Aug 27, 2013
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#ifndef __MAPFILE_MAPLOAD
#define __MAPFILE_MAPLOAD


void mapLoadMeta(fired::Map *map, FILE *fp);
void mapLoadTiles(fired::Map *map, FILE *fp);
void mapLoadCollectorItems(fired::MapObjectCollector *obj, FILE *fp);
void mapLoadObject(fired::Map *map, fired::BaseMapObject obj, FILE *fp);
void mapLoadObjects(fired::Map *map, FILE *fp);
void mapLoadSpawns(fired::Map *map, FILE *fp);

#endif
