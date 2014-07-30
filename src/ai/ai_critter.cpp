/***********************************************************************
     * File       : ai_critter.cpp
     * Created    : Aug 17, 2013
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#include "game.hpp"



/***********************************************************************
     * CritterAI
     * constructor

***********************************************************************/
fired::CritterAI::CritterAI(fired::Creature *_owner, fired::World *_world) : BaseAI(_owner, _world) {
	moving  = 0;
	jumping = 0;
}



/***********************************************************************
     * CritterAI
     * update

***********************************************************************/
void fired::CritterAI::update() {
	moveTimer.process();
	jumpTimer.process();

	if (!moveTimer.isActive()) {
		moveTimer.setTimer(4.0f + random() % 4);
		if (moving)
			moving = 0;
		else {
			moving = (random() % 2) ? 1 : -1;
			if (random() % 2) {
				jumpTimer.setTimer(2.0f + abs(getRandomOffset(moveTimer.timer - 2.0f)));
				jumping = 1;
			}
		}
	}

	if (!moving) return;

	if (jumping && !jumpTimer.isActive()) {
		jumping = 0;
		owner->character->jump();
	}

	if (moving == 1) owner->character->moveRight();
	else             owner->character->moveLeft();
}
