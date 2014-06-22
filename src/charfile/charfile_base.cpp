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
	struct stat buf;
	FILE *fp;

	if (stat("data/chars", &buf) == -1) MKDIR("data/chars");
	if ((fp = fopen(filename, "wb")) == NULL) return;

	saveCharMeta(character, fp);
	saveCharAttr(character, fp);
	saveCharInv(character, fp);

	fclose(fp);
}



/***********************************************************************
     * loadChar

***********************************************************************/
void loadChar(fired::Character *character, const char *filename) {
	FILE *fp = fopen(filename, "rb");
	if (!fp) return;

	loadCharMeta(character, fp);
	loadCharAttr(character, fp);
	loadCharInv(character, fp);

	fclose(fp);
}
