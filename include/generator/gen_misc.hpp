/***********************************************************************
     * File       : gen_misc.hpp
     * Created    : Jan 22, 2014
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#ifndef __GEN_MISC
#define __GEN_MISC


void genClear(int xSize, int ySize);
void genBar(int x, int startHeight, int endHeight, int tileset, bool isWall);
void genFill(int x1, int y1, int x2, int y2, int tileset, bool isWall);

#endif
