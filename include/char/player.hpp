#ifndef __PLAYER
#define __PLAYER

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
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
		void init(fired::Game *_game, fired::Camera *_cam, b2World *physWorld);
		void deinit();
		void update();

		void checkControls();
		fired::Phys *getPhys() { return &character.phys; };
	};
}

#endif
