#include "game.hpp"


//======================================================================


fired::MeleeAI::MeleeAI(fired::Creature *_owner, fired::World *_world) {
	target = NULL;
	owner  = _owner;
	world  = _world;
}

//======================================================================


void fired::MeleeAI::update() {
	if (target) if (target->isDead()) target = NULL;
	if (!target) selectTarget();

	owner->getChar()->setAiming(atan2(target->phys.center.y - owner->getChar()->phys.center.y, 
	                                  target->phys.center.x - owner->getChar()->phys.center.x));

	if (target->phys.center.x < owner->getChar()->phys.center.x) owner->getChar()->moveLeft();
	else owner->getChar()->moveRight();
}

//======================================================================


void fired::MeleeAI::selectTarget() {
	float minDist, dist;
	minDist = -1;

	for (unsigned int i = 0; i < world->chars.size(); i++)
		if (owner->getChar()->isEnemy(world->chars[i]->getFraction())) {
			dist = vLen(owner->getChar()->phys.center - world->chars[i]->phys.center);

			if (minDist == -1) {
				minDist = dist;
				target = world->chars[i];
			} else if (dist < minDist) {
				minDist = dist;
				target = world->chars[i];
			}
		}
}
