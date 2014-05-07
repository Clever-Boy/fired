/***********************************************************************
     * File       : charfile_load.cpp
     * Created    : May 07, 2014
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#include "game.hpp"



/***********************************************************************
     * loadCharAttr

***********************************************************************/
void loadCharAttr(fired::Character *character, FILE *fp) {
	fread(&character->attr, sizeof(character->attr), 1, fp);
}
