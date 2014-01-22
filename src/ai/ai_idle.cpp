/***********************************************************************
     * File       : ai_idle.cpp
     * Created    : Aug 12, 2013
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#include "game.hpp"



/***********************************************************************
     * IdleAI
     * constructor

***********************************************************************/
fired::IdleAI::IdleAI(fired::Creature *_owner, fired::World *_world) {
	target = NULL;
	owner  = _owner;
	world  = _world;
}



/***********************************************************************
     * IdleAI
     * update

***********************************************************************/
void fired::IdleAI::update() {
	return;
}
