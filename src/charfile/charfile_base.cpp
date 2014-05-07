/***********************************************************************
     * File       : charfile_base.cpp
     * Created    : May 07, 2014
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#include "game.hpp"



/***********************************************************************
     * saveChar

***********************************************************************/
void saveChar(fired::Character *character, const char *filename) {
	FILE *fp = fopen(filename, "w");
	if (!fp) return;

	saveCharAttr(character, fp);

	fclose(fp);
}



/***********************************************************************
     * loadChar

***********************************************************************/
void loadChar(fired::Character *character, const char *filename) {
	FILE *fp = fopen(filename, "r");
	if (!fp) return;

	loadCharAttr(character, fp);

	fclose(fp);
}
