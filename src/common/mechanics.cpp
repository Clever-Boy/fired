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



/***********************************************************************
     * armorReduction

***********************************************************************/
void calcStats(fired::CharacterStats *stats, fired::CharacterAttributes *attr) {
	stats->accel    = (2 * attr->dexterity    + attr->strength    ) * SKILL_ACCEL_K;
	stats->speed    = (2 * attr->dexterity    + attr->strength    ) * SKILL_SPEED_K;
	stats->aimrange = (2 * attr->constitution + attr->intelligence) * SKILL_AIMRANGE_K;
	stats->jump     = (2 * attr->strength     + attr->dexterity   ) * SKILL_JUMP_K;
	stats->armor    = (2 * attr->constitution + attr->dexterity   ) * SKILL_ARMOR_K;
	stats->maxHP    = (2 * attr->strength     + attr->constitution) * SKILL_MAXHP_K;
}
