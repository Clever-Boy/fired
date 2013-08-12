#ifndef __CREATURE
#define __CREATURE


#include <SFML/Graphics.hpp>
#include "prototypes.hpp"
#include "character.hpp"
#include "stats.hpp"
#include "phys.hpp"


namespace fired {
	struct BaseCreature {
		char  name[32];
		char  model[32];
		char  weapon[32];
		char  ai[32];
		char  fraction[32];
		float modelScale;

		CharacterStats stats;
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
