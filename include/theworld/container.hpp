#ifndef __CONTAINER
#define __CONTAINER


#include <SFML/Graphics.hpp>
#include "prototypes.hpp"


namespace fired {
	class Container {
	private:
		fired::Game      *game;
		fired::Settings  *settings;
		sf::RenderWindow *app;
		fired::World     *world;


	public:
		void init(fired::Game *_game, fired::World *_world);
		void deinit();
	};
}

#endif
