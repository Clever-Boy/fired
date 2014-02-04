/***********************************************************************
     * File       : gensave.hpp
     * Created    : Aug 27, 2013
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#ifndef __GENSAVE
#define __GENSAVE

#include "generator.hpp"


void genSaveMeta(fired::MapGenerator *gen, FILE *fp);
void genSaveTiles(fired::MapGenerator *gen, FILE *fp);
void genSaveCollectorItems(fired::BaseMapObjectCollector *obj, FILE *fp);
void genSaveObject(fired::BaseMapObject obj, FILE *fp);
void genSaveObjects(fired::MapGenerator *gen, FILE *fp);

#endif
