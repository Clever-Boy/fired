/***********************************************************************
     * File       : charfile_save.cpp
     * Created    : May 07, 2014
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#include "game.hpp"



/***********************************************************************
     * saveCharMeta

***********************************************************************/
void saveCharMeta(fired::Character *character, FILE *fp) {
	fwrite(&character->HP   , sizeof(character->HP)   , 1, fp);
	fwrite(&character->XP   , sizeof(character->XP)   , 1, fp);
	fwrite(&character->level, sizeof(character->level), 1, fp);
}



/***********************************************************************
     * saveCharAttr

***********************************************************************/
void saveCharAttr(fired::Character *character, FILE *fp) {
	fwrite(&character->attr, sizeof(character->attr), 1, fp);
}



/***********************************************************************
     * saveCharInv

***********************************************************************/
void saveCharInv(fired::Character *character, FILE *fp) {
	fwrite(&character->inventory->credits, sizeof(character->inventory->credits), 1, fp);
}
