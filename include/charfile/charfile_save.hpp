/***********************************************************************
     * File       : charfile_save.hpp
     * Created    : May 07, 2014
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#ifndef __CHARFILE_SAVE
#define __CHARFILE_SAVE


void saveCharMeta(fired::Character *character, FILE *fp);
void saveCharAttr(fired::Character *character, FILE *fp);
void saveCharInv(fired::Character *character, FILE *fp);
void saveCharItem(fired::InventoryItem *item, FILE *fp);

#endif
