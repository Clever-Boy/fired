/***********************************************************************
     * File       : charfile_gen.cpp
     * Created    : May 07, 2014
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#include "game.hpp"



/***********************************************************************
     * genCharMeta

***********************************************************************/
void genCharMeta(FILE *fp) {
	long HP    = 1;
	long XP    = 0;
	int  level = 1;

	fwrite(&HP   , sizeof(HP)   , 1, fp);
	fwrite(&XP   , sizeof(XP)   , 1, fp);
	fwrite(&level, sizeof(level), 1, fp);
}



/***********************************************************************
     * genCharAttr

***********************************************************************/
void genCharAttr(FILE *fp) {
	fired::CharacterAttributes attr;
	fwrite(&attr, sizeof(attr), 1, fp);
}



/***********************************************************************
     * genCharInv

***********************************************************************/
void genCharInv(FILE *fp) {
	int credits = 0;
	fwrite(&credits, sizeof(credits), 1, fp);


	for (unsigned int i = 0; i < 10; i++)
		genCharItem(fp);


	for (unsigned int i = 0; i < 10; i++)
		for (unsigned int j = 0; j < 5; j++)
			genCharItem(fp);
}



/***********************************************************************
     * genCharItem

***********************************************************************/
void genCharItem(FILE *fp) {
	int          ID    = 0;
	unsigned int count = 0;

	fwrite(&ID, sizeof(ID), 1, fp);
	fwrite(&count, sizeof(count), 1, fp);
}
