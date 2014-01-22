/***********************************************************************
     * File       : sqlite_crypt.hpp
     * Created    : Aug 19, 2013
     * Copyright  : (C) 2013 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#ifndef __SQLITE_CRYPT
#define __SQLITE_CRYPT


void sqlite_crypt(char *sql, unsigned int sqllen, const char *key, unsigned int keylen);

#endif
