/***********************************************************************
     * File       : charfile_base.hpp
     * Created    : May 07, 2014
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#ifndef __CHARFILE_BASE
#define __CHARFILE_BASE


void saveChar(fired::Character *character, const char *filename);
void loadChar(fired::Character *character, const char *filename);

#endif
