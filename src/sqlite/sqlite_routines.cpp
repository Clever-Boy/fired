/***********************************************************************
     * File       : sqlite_routines.cpp
     * Created    : Aug 19, 2013
     * Copyright  : (C) 2013 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#include "sqlite_routines.hpp"



/***********************************************************************
     * appendText

***********************************************************************/
char *appendText(char *zIn, char const *zAppend, char quote){
	int len;
	int i;
	int nAppend = strlen(zAppend);
	int nIn = (zIn?strlen(zIn):0);

	len = nAppend+nIn+1;
	if(quote) {
		len += 2;
		for(i=0; i<nAppend; i++) if(zAppend[i]==quote) len++;
	}

	zIn = (char *)realloc(zIn, len);
	if( !zIn ) return 0;

	if (quote) {
		char *zCsr = &zIn[nIn];
		*zCsr++ = quote;

		for(i=0; i<nAppend; i++){
			*zCsr++ = zAppend[i];
			if( zAppend[i]==quote ) *zCsr++ = quote;
		}

		*zCsr++ = quote;
		*zCsr++ = '\0';
		assert( (zCsr-zIn)==len );
	} else {
		memcpy(&zIn[nIn], zAppend, nAppend);
		zIn[len-1] = '\0';
	}

	return zIn;
}



/***********************************************************************
     * run_table_dump_query

***********************************************************************/
int run_table_dump_query(struct callback_data *p, const char *zSelect, const char *zFirstRow) {
	sqlite3_stmt *pSelect;
	int rc;
	int nResult;
	int i;
	const char *z;

	rc = sqlite3_prepare(p->db, zSelect, -1, &pSelect, 0);
	if (rc!=SQLITE_OK || !pSelect) {
		p->nErr++;
		return rc;
	}

	rc = sqlite3_step(pSelect);
	nResult = sqlite3_column_count(pSelect);
	while( rc==SQLITE_ROW ){
		if (zFirstRow) {
			*p->out = appendText(*p->out, zFirstRow, 0);
			zFirstRow = 0;
		}

		z = (const char*)sqlite3_column_text(pSelect, 0);
		*p->out = appendText(*p->out, z, 0);

		for (i=1; i<nResult; i++) {
			*p->out = appendText(*p->out, "," , 0);
			*p->out = appendText(*p->out, (char *)sqlite3_column_text(pSelect, i), 0);
		}
		if (z==0) z = "";

		while (z[0] && (z[0]!='-' || z[1]!='-')) z++;

		if (z[0]) *p->out = appendText(*p->out, "\n;\n", 0);
		else *p->out = appendText(*p->out, ";\n", 0);

		rc = sqlite3_step(pSelect);
	}

	rc = sqlite3_finalize(pSelect);
	if( rc!=SQLITE_OK ){
		p->nErr++;
	}

	return rc;
}



/***********************************************************************
     * dump_callback

***********************************************************************/
int dump_callback(void *pArg, int nArg, char **azArg, char **){
	int rc;
	const char *zTable;
	const char *zType;
	const char *zSql;
	const char *zPrepStmt = 0;
	struct callback_data *p = (struct callback_data *)pArg;

	if(nArg != 3) return 1;

	zTable = azArg[0];
	zType  = azArg[1];
	zSql   = azArg[2];
  
	if (strcmp(zTable, "sqlite_sequence") == 0)  zPrepStmt = "DELETE FROM sqlite_sequence;\n";
	else if(strcmp(zTable, "sqlite_stat1") == 0) *p->out = appendText(*p->out, "ANALYZE sqlite_master;\n", 0);
	else if (strncmp(zTable, "sqlite_", 7) == 0) return 0;
	else if (strncmp(zSql, "CREATE VIRTUAL TABLE", 20) == 0) {
		char *zIns;
		if( !p->writableSchema ){
			*p->out = appendText(*p->out, "PRAGMA writable_schema=ON;\n", 0);
			p->writableSchema = 1;
		}

		zIns = sqlite3_mprintf("INSERT INTO sqlite_master(type,name,tbl_name,rootpage,sql)"
		                       "VALUES('table','%q','%q',0,'%q');", zTable, zTable, zSql);

		*p->out = appendText(*p->out, zIns, 0);
		*p->out = appendText(*p->out, "\n", 0);
		sqlite3_free(zIns);
		return 0;
	} else {
		*p->out = appendText(*p->out, zSql, 0);
		*p->out = appendText(*p->out, ";\n", 0);
	}

	if( strcmp(zType, "table")==0 ){
		sqlite3_stmt *pTableInfo = 0;
		char *zSelect = 0;
		char *zTableInfo = 0;
		char *zTmp = 0;
		int nRow = 0;

		zTableInfo = appendText(zTableInfo, "PRAGMA table_info(", 0);
		zTableInfo = appendText(zTableInfo, zTable, '"');
		zTableInfo = appendText(zTableInfo, ");", 0);

		rc = sqlite3_prepare(p->db, zTableInfo, -1, &pTableInfo, 0);
		free(zTableInfo);
		if( rc!=SQLITE_OK || !pTableInfo ) return 1;

		zSelect = appendText(zSelect, "SELECT 'INSERT INTO ' || ", 0);
		zTmp = appendText(zTmp, zTable, '"');
		if (zTmp) {
			zSelect = appendText(zSelect, zTmp, '\'');
			free(zTmp);
		}

		zSelect = appendText(zSelect, " || ' VALUES(' || ", 0);
		rc = sqlite3_step(pTableInfo);

		while (rc == SQLITE_ROW) {
			const char *zText = (const char *)sqlite3_column_text(pTableInfo, 1);
			zSelect = appendText(zSelect, "quote(", 0);
			zSelect = appendText(zSelect, zText, '"');
			rc = sqlite3_step(pTableInfo);

			if( rc==SQLITE_ROW ) zSelect = appendText(zSelect, "), ", 0);
			else zSelect = appendText(zSelect, ") ", 0);

			nRow++;
		}

		rc = sqlite3_finalize(pTableInfo);
		if (rc != SQLITE_OK || nRow == 0) {
			free(zSelect);
			return 1;
		}

		zSelect = appendText(zSelect, "|| ')' FROM  ", 0);
		zSelect = appendText(zSelect, zTable, '"');

		rc = run_table_dump_query(p, zSelect, zPrepStmt);
		if(rc == SQLITE_CORRUPT) {
			zSelect = appendText(zSelect, " ORDER BY rowid DESC", 0);
			run_table_dump_query(p, zSelect, 0);
		}

		free(zSelect);
	}

	return 0;
}



/***********************************************************************
     * run_schema_dump_query

***********************************************************************/
int run_schema_dump_query(struct callback_data *p, const char *zQuery) {
	char *zErr = 0;
	return sqlite3_exec(p->db, zQuery, dump_callback, p, &zErr);
}



/***********************************************************************
     * dumpDb

***********************************************************************/
void dumpDb(sqlite3 *db, char **sql) {
	struct callback_data p; 

	p.out = sql;
	p.db  = db;

	*sql = appendText(*sql, "PRAGMA foreign_keys=OFF;\n", 0);
	*sql = appendText(*sql, "BEGIN TRANSACTION;\n", 0);

	sqlite3_exec(db, "SAVEPOINT dump; PRAGMA writable_schema=ON", 0, 0, 0);

	run_schema_dump_query(&p, "SELECT name, type, sql FROM sqlite_master "
	                          "WHERE sql NOT NULL AND type=='table' AND name!='sqlite_sequence'");

	run_schema_dump_query(&p, "SELECT name, type, sql FROM sqlite_master "
	                          "WHERE name=='sqlite_sequence'");

	run_table_dump_query(&p, "SELECT sql FROM sqlite_master "
	                         "WHERE sql NOT NULL AND type IN ('index','trigger','view')", 0);

	sqlite3_exec(db, "PRAGMA writable_schema=OFF;", 0, 0, 0);
	sqlite3_exec(db, "RELEASE dump;", 0, 0, 0);
	*sql = appendText(*sql, "COMMIT;\n", 0);
}
