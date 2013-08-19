#include "sqlite_crypt.hpp"
#include "sqlite_routines.hpp"


//======================================================================


void sqliteSaveDB(sqlite3 *db, const char *filename, bool crypt) {
	char *sql = NULL;
	unsigned int size;
	dumpDb(db, &sql);

	size = strlen(sql);
	if (crypt) sqlite_crypt(sql, size, SQLITE_KEY, strlen(SQLITE_KEY));

	FILE *fp = fopen(filename, "w");
	fwrite(sql, size, 1, fp);
	fclose(fp);
	free(sql);
}

//======================================================================


void sqliteLoadDB(sqlite3 **db, const char *filename, bool crypt) {
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

	if (crypt) sqlite_crypt(sql, filesize, SQLITE_KEY, strlen(SQLITE_KEY));
	sqlite3_exec(*db, sql, 0, 0, 0);
	free(sql);
}
