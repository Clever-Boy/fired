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
		char  model[64];
		char  weapon[64];
		char  ai[64];
		char  fraction[64];
		float modelScale;

		fired::CharacterStats stats;
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
