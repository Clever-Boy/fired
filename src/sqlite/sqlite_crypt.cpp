#include "sqlite_crypt.hpp"


//======================================================================


void sqlite_crypt(char *sql, unsigned int sqllen, const char *key, unsigned int keylen) {
	unsigned int keypos = 0;

	for (unsigned int i = 0; i < sqllen; i++) {
		sql[i] ^= key[keypos++];
		if (keypos == keylen) keypos = 0;
	}
}
