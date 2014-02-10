/***********************************************************************
     * File       : sqlite_routines.cpp
     * Created    : Aug 19, 2013
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#include "sqlite.hpp"



/***********************************************************************
     * sqlite_append

***********************************************************************/
char *sqlite_append(char *zIn, char const *zAppend, char quote){
	int nAppend = strlen(zAppend);
	int nIn = (zIn?strlen(zIn):0);
	int len = nAppend + nIn + 1 + (quote ? 2 : 0);

	if (quote) for (int i = 0; i < nAppend; i++) if (zAppend[i] == quote) len++;

	zIn = (char *)realloc(zIn, len);
	if (!zIn) return NULL;

	char *zCsr = &zIn[nIn];
	if (quote) *zCsr++ = quote;

	for (int i = 0; i < nAppend; i++) {
		*zCsr++ = zAppend[i];
		if (quote && zAppend[i]==quote) *zCsr++ = quote;
	}

	if (quote) *zCsr++ = quote;
	zIn[len-1] = '\0';

	return zIn;
}



/***********************************************************************
     * sqlite_dump_table

***********************************************************************/
int sqlite_dump_table(struct callback_data *p, const char *zSelect) {
	sqlite3_stmt *pSelect;
	int rc;
	int nResult;

	rc = sqlite3_prepare(p->db, zSelect, -1, &pSelect, 0);
	if (rc != SQLITE_OK) return rc;

	rc = sqlite3_step(pSelect);
	nResult = sqlite3_column_count(pSelect);

	while (rc == SQLITE_ROW) {
		*p->out = sqlite_append(*p->out, (const char*)sqlite3_column_text(pSelect, 0), 0);
		for (int i = 1; i < nResult; i++) {
			*p->out = sqlite_append(*p->out, "," , 0);
			*p->out = sqlite_append(*p->out, (char *)sqlite3_column_text(pSelect, i), 0);
		}

		*p->out = sqlite_append(*p->out, ";\n", 0);
		rc = sqlite3_step(pSelect);
	}

	rc = sqlite3_finalize(pSelect);
	return rc;
}



/***********************************************************************
     * sqlite_dump_callback

***********************************************************************/
int sqlite_dump_callback(void *pArg, int, char **azArg, char **){
	int rc;
	const char *zTable = azArg[0];
	struct callback_data *p = (struct callback_data *)pArg;

	*p->out = sqlite_append(*p->out, azArg[1], 0);
	*p->out = sqlite_append(*p->out, ";\n", 0);

	sqlite3_stmt *pTableInfo = 0;
	char *zSelect = 0;
	char *zTableInfo = 0;
	int nRow = 0;

	zTableInfo = sqlite_append(zTableInfo, "PRAGMA table_info(", 0);
	zTableInfo = sqlite_append(zTableInfo, zTable, '"');
	zTableInfo = sqlite_append(zTableInfo, ");", 0);

	rc = sqlite3_prepare(p->db, zTableInfo, -1, &pTableInfo, 0);
	free(zTableInfo);
	if( rc!=SQLITE_OK || !pTableInfo ) return 1;

	zSelect = sqlite_append(zSelect, "SELECT 'INSERT INTO ' || \'", 0);
	zSelect = sqlite_append(zSelect, zTable, '"');
	zSelect = sqlite_append(zSelect, "\' || ' VALUES(' || ", 0);

	rc = sqlite3_step(pTableInfo);
	while (rc == SQLITE_ROW) {
		zSelect = sqlite_append(zSelect, "quote(", 0);
		zSelect = sqlite_append(zSelect, (const char *)sqlite3_column_text(pTableInfo, 1), '"');
		zSelect = sqlite_append(zSelect, ")", 0);
		rc = sqlite3_step(pTableInfo);

		if( rc==SQLITE_ROW ) zSelect = sqlite_append(zSelect, ", ", 0);

		nRow++;
	}

	rc = sqlite3_finalize(pTableInfo);
	if (rc != SQLITE_OK || nRow == 0) {
		free(zSelect);
		return 1;
	}

	zSelect = sqlite_append(zSelect, "|| ')' FROM  ", 0);
	zSelect = sqlite_append(zSelect, zTable, '"');

	sqlite_dump_table(p, zSelect);
	free(zSelect);

	return 0;
}



/***********************************************************************
     * sqlite_dumpDb

***********************************************************************/
void sqlite_dump(sqlite3 *db, char **sql) {
	struct callback_data p; 

	p.out = sql;
	p.db  = db;

	*sql = sqlite_append(*sql, "PRAGMA foreign_keys=OFF;\n", 0);
	*sql = sqlite_append(*sql, "BEGIN TRANSACTION;\n", 0);

	sqlite3_exec(db, "SAVEPOINT dump; PRAGMA writable_schema=ON", 0, 0, 0);
	sqlite3_exec(db, "SELECT name, sql FROM sqlite_master", sqlite_dump_callback, &p, 0);
	sqlite3_exec(db, "PRAGMA writable_schema=OFF; RELEASE dump", 0, 0, 0);

	*sql = sqlite_append(*sql, "COMMIT;\n", 0);
}
