#ifndef __PLAYER
#define __PLAYER


#include <SFML/Graphics.hpp>
#include "prototypes.hpp"
#include "character.hpp"
#include "stats.hpp"
#include "phys.hpp"


namespace fired {
	class Player {
	private:
		fired::Game      *game;
		fired::Settings  *settings;
		sf::RenderWindow *app;

		fired::Character character;
		fired::Crosshair crosshair;


	public:
		void init(fired::Game *_game, fired::Camera *_cam, sf::Vector2f _startpos, fired::World *world);
		void deinit();
		void update();

		void checkControls();
		fired::Phys *getPhys() { return &character.phys; };
	};
}

#endif
