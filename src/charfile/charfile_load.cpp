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



/***********************************************************************
     * loadCharInv

***********************************************************************/
void loadCharInv(fired::Character *character, FILE *fp) {
	fread(&character->inventory->credits, sizeof(character->inventory->credits), 1, fp);
}



/***********************************************************************
     * loadCharItem

***********************************************************************/
void loadCharItem(fired::InventoryItem *item, FILE *fp) {
	int          ID;
	unsigned int count;

	fread(&ID, sizeof(ID), 1, fp);
	fread(&count, sizeof(count), 1, fp);

	if (count) {
		item->base = container->items[ID];
		item->count = count;
	}
}
