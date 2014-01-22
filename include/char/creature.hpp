/***********************************************************************
     * File       : creature.hpp
     * Created    : Aug 06, 2013
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#ifndef __CREATURE
#define __CREATURE


namespace fired {
	struct BaseCreature;
	struct Creature;
}


#include "character.hpp"
#include "ai.hpp"


namespace fired {
	struct BaseCreature {
		char  name[64];
		char  ai[64];
		float modelScale;
		int   fraction;

		fired::CharacterStats  stats;
		fired::BaseModel      *model;
		fired::BaseWeapon     *weapon;

		std::vector<fired::LootItem*> loot;


		 BaseCreature();
		~BaseCreature();
	};


	struct Creature {
		fired::Character *character;
		fired::BaseAI    *ai;


		 Creature(fired::Camera *_cam, sf::Vector2f _startpos, fired::World *world, fired::BaseCreature *base);
		~Creature();

		void update();
	};
}

#endif
