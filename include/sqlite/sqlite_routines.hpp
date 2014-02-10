/***********************************************************************
     * File       : sqlite_routines.hpp
     * Created    : Aug 19, 2013
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#ifndef __SQLITE_ROUTINES
#define __SQLITE_ROUTINES


#include <stdio.h>
#include <sqlite3.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>


struct callback_data {
	sqlite3  *db;
	char    **out;
};


char *sqlite_append(char *zIn, char const *zAppend, char quote);
int   sqlite_dump_table(struct callback_data *p, const char *zSelect);
int   sqlite_dump_callback(void *pArg, int nArg, char **azArg, char **azCol);
void  sqlite_dump(sqlite3 *db, char **sql);


#endif
