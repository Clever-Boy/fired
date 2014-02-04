/***********************************************************************
     * File       : mapsave.hpp
     * Created    : Aug 27, 2013
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#ifndef __MAPSAVE
#define __MAPSAVE


void mapSaveMeta(fired::Map *map, FILE *fp);
void mapSaveTiles(fired::Map *map, FILE *fp);
void mapSaveCollectorItems(fired::MapObjectCollector *obj, FILE *fp);
void mapSaveObject(fired::MapObject obj, FILE *fp);
void mapSaveObjects(fired::Map *map, FILE *fp);

#endif
