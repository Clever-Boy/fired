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

	saveCharItem(&character->inventory->helm, fp);
	saveCharItem(&character->inventory->body, fp);
	saveCharItem(&character->inventory->arms, fp);
	saveCharItem(&character->inventory->fist, fp);
	saveCharItem(&character->inventory->legs, fp);
	saveCharItem(&character->inventory->shoe, fp);

	saveCharItem(&character->inventory->primaryWeapon  , fp);
	saveCharItem(&character->inventory->secondaryWeapon, fp);
	saveCharItem(&character->inventory->primaryAmmo    , fp);
	saveCharItem(&character->inventory->secondaryAmmo  , fp);

	for (unsigned int i = 0; i < 10; i++)
		for (unsigned int j = 0; j < 5; j++)
			saveCharItem(&character->inventory->items[i][j], fp);
}



/***********************************************************************
     * saveCharItem

***********************************************************************/
void saveCharItem(fired::InventoryItem *item, FILE *fp) {
	int          ID    = 0;
	unsigned int count = 0;

	if (item->base) {
		ID    = item->base->ID;
		count = item->count;
	}

	fwrite(&ID, sizeof(ID), 1, fp);
	fwrite(&count, sizeof(count), 1, fp);
}
