#ifndef __SQLITE_API
#define __SQLITE_API


#include <sqlite3.h>


void sqliteSaveDB(sqlite3 *db, const char *filename, bool crypt, const char *key);
void sqliteLoadDB(sqlite3 **db, const char *filename, bool crypt, const char *key);

#endif
