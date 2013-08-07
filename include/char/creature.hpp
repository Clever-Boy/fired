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
		float modelScale;

		CharacterStats stats;
	};


	class Creature {
	private:
		fired::Game      *game;
		fired::Settings  *settings;
		sf::RenderWindow *app;

		fired::Character character;
		bool left; // Temporary for pseudo AI

	public:
		void init(fired::Game *_game, fired::Camera *_cam, sf::Vector2f _startpos, fired::World *world, fired::BaseCreature *base);
		void deinit();
		void update();

		fired::Phys *getPhys() { return &character.phys; };
		fired::Character *getChar() { return &character; };
	};
}

#endif
