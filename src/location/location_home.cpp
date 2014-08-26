/***********************************************************************
     * File       : location_home.cpp
     * Created    : Aug 26, 2014
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#include "game.hpp"



/***********************************************************************
     * LocationHome
     * constructor

***********************************************************************/
fired::LocationHome::LocationHome(fired::Camera *cam, fired::World *world) {
	map = new fired::Map(cam, world);
}



/***********************************************************************
     * LocationHome
     * destructor

***********************************************************************/
fired::LocationHome::~LocationHome() {
	delete map;
}
