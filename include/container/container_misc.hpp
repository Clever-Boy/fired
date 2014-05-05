/***********************************************************************
     * File       : container_misc.hpp
     * Created    : May 05, 2015
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#ifndef __CONTAINER_MISC
#define __CONTAINER_MISC


void loadContent(sqlite3 *db, int (*callback)(void*,int,char**,char**), const char *sql);
void loadModelBodypart(const char* s, fired::BaseModelBodypart *bodypart, fired::BodypartType type);
void loadCreatureLoot(fired::BaseCreature *current, const char *lootStr);

#endif
