/***********************************************************************
     * File       : ai_basic.cpp
     * Created    : Aug 17, 2013
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#include "game.hpp"



/***********************************************************************
     * BasicAI
     * update

***********************************************************************/
void fired::BasicAI::update() {
	if (target) if (target->dead) target = NULL;
	selectTarget();
	if (!target) return;

	owner->character->setAiming(atan2(target->phys.center.y - owner->character->phys.center.y, 
	                                  target->phys.center.x - owner->character->phys.center.x));

	owner->character->phys.jumpdown = false;


	if (target->phys.center.x < owner->character->phys.center.x)
		owner->character->moveLeft();
	else
		owner->character->moveRight();


	if (target->phys.center.y < owner->character->phys.center.y - 32)
		owner->character->jump();
	else if (target->phys.center.y > owner->character->phys.center.y + 32)
		owner->character->jumpdown();


	if (vLen(owner->character->phys.center - target->phys.center) < owner->character->phys.size.x / 2 + owner->character->getRange()) {
		owner->character->shot();
		owner->character->unshot();
	}
}



/***********************************************************************
     * BasicAI
     * selectTarget

***********************************************************************/
void fired::BasicAI::selectTarget() {
	float minDist, dist;
	minDist = -1;

	for (unsigned int i = 0; i < world->chars.size(); i++) {
		if (world->chars[i]->dead) continue;

		if (owner->character->isEnemy(world->chars[i]->fraction)) {
			dist = vLen(owner->character->phys.center - world->chars[i]->phys.center);
			if (dist > owner->character->stats.aimrange) continue;
			if (target && dist > owner->character->stats.aimrange * 0.66f) continue;

			if (minDist == -1) {
				minDist = dist;
				target = world->chars[i];
			} else if (dist < minDist) {
				minDist = dist;
				target = world->chars[i];
			}
		}
	}
}
