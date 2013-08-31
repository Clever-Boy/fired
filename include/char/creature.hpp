#ifndef __CREATURE
#define __CREATURE


namespace fired {
	class BaseCreature;
	class Creature;
}


#include "character.hpp"
#include "ai.hpp"


namespace fired {
	struct BaseCreature {
		char  name[32];
		char  model[32];
		char  weapon[32];
		char  ai[32];
		char  fraction[32];
		float modelScale;

		fired::CharacterStats stats;
		std::vector<fired::LootItem*> loot;

		 BaseCreature();
		~BaseCreature();
	};


	class Creature {
	private:
		fired::Character *character;
		fired::BaseAI    *ai;


	public:
		 Creature(fired::Camera *_cam, sf::Vector2f _startpos, fired::World *world, fired::BaseCreature *base);
		~Creature();
		void update();

		fired::Phys *getPhys() { return &character->phys; };
		fired::Character *getChar() { return character; };
	};
}

#endif
