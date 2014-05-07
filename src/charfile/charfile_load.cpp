/***********************************************************************
     * File       : charfile_load.cpp
     * Created    : May 07, 2014
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#include "game.hpp"



/***********************************************************************
     * loadCharMeta

***********************************************************************/
void loadCharMeta(fired::Character *character, FILE *fp) {
	fread(&character->HP   , sizeof(character->HP)   , 1, fp);
	fread(&character->XP   , sizeof(character->XP)   , 1, fp);
	fread(&character->level, sizeof(character->level), 1, fp);
}



/***********************************************************************
     * loadCharAttr

***********************************************************************/
void loadCharAttr(fired::Character *character, FILE *fp) {
	fread(&character->attr, sizeof(character->attr), 1, fp);
}
