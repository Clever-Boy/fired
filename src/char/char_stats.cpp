/***********************************************************************
     * File       : char_stats.cpp
     * Created    : Apr 01, 2014
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#include "game.hpp"



/***********************************************************************
     * CharacterStats
     * operator+

***********************************************************************/
fired::CharacterStats fired::CharacterStats::operator+(const CharacterStats& r) {
	fired::CharacterStats l = *this;

	l.speed    += r.speed;
	l.accel    += r.accel;
	l.aimrange += r.aimrange;
	l.jump     += r.jump;
	l.accuracy += r.accuracy;
	l.xpfactor += r.xpfactor;
	l.maxHP    += r.maxHP;
	l.armor    += r.armor;

	return l;
}
