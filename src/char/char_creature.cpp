/***********************************************************************
     * File       : char_creature.cpp
     * Created    : Aug 06, 2013
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#include "game.hpp"



/***********************************************************************
     * BaseCreature
     * constructor

***********************************************************************/
fired::BaseCreature::BaseCreature() {
	loot.clear();
}



/***********************************************************************
     * BaseCreature
     * destructor

***********************************************************************/
fired::BaseCreature::~BaseCreature() {
	deleteList(loot);
	delete colors;
}



/***********************************************************************
     * Creature
     * constructor

***********************************************************************/
fired::Creature::Creature(fired::Camera *_cam, sf::Vector2f _startpos, fired::World *world, fired::BaseCreature *base) {
	character = new fired::Character(_cam, _startpos, world, base);
	character->generateLoot(&base->loot);
	ai = container->getAI(base->ai, this, world);
}



/***********************************************************************
     * Creature
     * destructor

***********************************************************************/
fired::Creature::~Creature() {
	delete character;
	delete ai;
}



/***********************************************************************
     * Creature
     * update

***********************************************************************/
void fired::Creature::update() {
	ai->update();
	character->update();
}
