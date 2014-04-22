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
void genBar(int x, int startHeight, int endHeight, bool isWall);
void genFill(int x1, int y1, int x2, int y2, bool isWall);
void genFillRect(sf::IntRect rect, bool isWall);

void addDecor(float x, float y, const char *name);
void addCollector(float x, float y, const char *name);
void addLightSource(float x, float y, const char *name);
void addPlatform(int x, int y, const char *name);

void addTileToPalette(const char *name);
void setBrush(const char *name);
void setEraser();

#endif
