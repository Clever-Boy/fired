/***********************************************************************
     * File       : mechanics.cpp
     * Created    : Sep 01, 2013
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#include "game.hpp"



/***********************************************************************
     * levelXP

***********************************************************************/
long levelXP(int level) {
	long res = 0;
	for (int i = 0; i < level; res += (i / 2 + 1) * 250, i++);
	return res;
}



/***********************************************************************
     * armorReduction

***********************************************************************/
float armorReduction(unsigned int armor) {
	return 1.0f - 100.0f / (100.0f + (float)armor);
}
