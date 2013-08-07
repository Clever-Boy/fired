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

		std::vector<fired::BaseWeapon*> weapons;

	public:
		void init(fired::Game *_game, fired::World *_world);
		void deinit();

		void loadWeapons();
		void loadWeapon(const char* filename);
		fired::BaseWeapon *getWeapon(const char* name);
	};
}

#endif
