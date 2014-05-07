/***********************************************************************
     * File       : misc_char.cpp
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

	fwrite(&character->attr, sizeof(character->attr), 1, fp);

	fclose(fp);
}



/***********************************************************************
     * loadChar

***********************************************************************/
void loadChar(fired::Character *character, const char *filename) {
	FILE *fp = fopen(filename, "r");
	if (!fp) return;

	fread(&character->attr, sizeof(character->attr), 1, fp);

	fclose(fp);
}
