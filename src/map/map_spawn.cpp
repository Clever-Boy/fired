/***********************************************************************
     * File       : map_spawn.cpp
     * Created    : Jul 24, 2013
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#include "game.hpp"



/***********************************************************************
     * MapSpawn
     * constructor

***********************************************************************/
fired::MapSpawn::MapSpawn(sf::IntRect _spawn, int _type) {
	type  = _type;
	spawn = _spawn;
}
