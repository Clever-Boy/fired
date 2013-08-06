#ifndef __CREATURE
#define __CREATURE


#include <SFML/Graphics.hpp>
#include "prototypes.hpp"
#include "character.hpp"
#include "stats.hpp"
#include "phys.hpp"


namespace fired {
	class Creature {
	private:
		fired::Game      *game;
		fired::Settings  *settings;
		sf::RenderWindow *app;

		fired::Character character;
		bool left; // Temporary for pseudo AI

	public:
		void init(fired::Game *_game, sf::Vector2f _startpos, fired::World *world);
		void deinit();
		void update();

		fired::Phys *getPhys() { return &character.phys; };
		fired::Character *getChar() { return &character; };
	};
}

#endif
