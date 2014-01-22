/***********************************************************************
     * File       : phys.cpp
     * Created    : Aug 06, 2013
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#include "game.hpp"



/***********************************************************************
     * Phys
     * constructor

***********************************************************************/
fired::Phys::Phys() {
	jumpdown      = false;
	jumpdownLevel = 0;
}



/***********************************************************************
     * Phys
     * calculate

***********************************************************************/
void fired::Phys::calculate() {
	rect   = sf::FloatRect(pos, size);
	center = pos + size / 2.0f;
}
