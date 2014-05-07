/***********************************************************************
     * File       : charfile_save.cpp
     * Created    : May 07, 2014
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#include "game.hpp"



/***********************************************************************
     * saveCharAttr

***********************************************************************/
void saveCharAttr(fired::Character *character, FILE *fp) {
	fwrite(&character->attr, sizeof(character->attr), 1, fp);
}
