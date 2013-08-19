#ifndef __SQLITE_CRYPT
#define __SQLITE_CRYPT


#define SQLITE_KEY "simple_"


void sqlite_crypt(char *sql, unsigned int sqllen, const char *key, unsigned int keylen);

#endif
