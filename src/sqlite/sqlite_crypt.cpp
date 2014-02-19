/***********************************************************************
     * File       : sqlite_crypt.cpp
     * Created    : Aug 19, 2013
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#include "sqlite.hpp"



/***********************************************************************
     * sqlite_crypt

***********************************************************************/
void sqlite_crypt(char *sql, unsigned int sqllen, const char *key, unsigned int keylen) {
	unsigned int keypos = 0;
	unsigned int step   = 1;

	for (unsigned int i = 0; i < sqllen; i++) {
		sql[i] ^= key[keypos += step];
		if (keypos >= keylen) step++;
		if (step   == keylen) step = 1;
		keypos %= keylen;
	}
}
