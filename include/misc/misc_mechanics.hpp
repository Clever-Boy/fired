/***********************************************************************
     * File       : misc_mechanics.hpp
     * Created    : Sep 01, 2013
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#ifndef __MISC_MECHANICS
#define __MISC_MECHANICS


long  levelXP(int level);
float armorReduction(unsigned int armor);
void  calcStats(fired::CharacterStats *stats, fired::CharacterAttributes *attr);
float accuracyReduction(float accuracy);

#endif
