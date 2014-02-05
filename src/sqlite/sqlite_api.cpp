/***********************************************************************
     * File       : sqlite_api.cpp
     * Created    : Aug 19, 2013
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#include "sqlite.hpp"



/***********************************************************************
     * sqliteSaveDB

***********************************************************************/
void sqliteSaveDB(sqlite3 *db, const char *filename, bool crypt, const char *key) {
	char *sql = NULL;
	unsigned int size;
	dumpDb(db, &sql);

	size = strlen(sql);
	if (crypt) sqlite_crypt(sql, size, key, strlen(key));

	FILE *fp = fopen(filename, "w");
	fwrite(sql, size, 1, fp);
	fclose(fp);
	free(sql);
}



/***********************************************************************
     * sqliteLoadDB

***********************************************************************/
void sqliteLoadDB(sqlite3 **db, const char *filename, bool crypt, const char *key) {
	char *sql = NULL;
	struct stat buf;
	unsigned int filesize;

	sqlite3_open(":memory:", db);
	stat(filename, &buf);
	filesize = buf.st_size;

	FILE *fp = fopen(filename, "r");
	sql = (char *)malloc(filesize + 1);
	fread(sql, filesize, 1, fp);
	sql[filesize] = 0;
	fclose(fp);

	if (crypt) sqlite_crypt(sql, filesize, key, strlen(key));
	sqlite3_exec(*db, sql, 0, 0, 0);
	free(sql);
}
