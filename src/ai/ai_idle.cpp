#include "game.hpp"


//======================================================================


fired::IdleAI::IdleAI(fired::Creature *_owner, fired::World *_world) {
	target = NULL;
	owner  = _owner;
	world  = _world;
}

//======================================================================


void fired::IdleAI::update() {
	return;
}
