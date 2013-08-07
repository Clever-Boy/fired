#ifndef __CONTAINER
#define __CONTAINER


#include <SFML/Graphics.hpp>
#include "prototypes.hpp"
#include "char.hpp"


namespace fired {
	class Container {
	private:
		fired::Game      *game;
		fired::Settings  *settings;
		sf::RenderWindow *app;
		fired::World     *world;

		std::vector<fired::BaseWeapon*> weapons;
		std::vector<fired::BaseBodypart*>   bodyparts;


	public:
		void init(fired::Game *_game, fired::World *_world);
		void deinit();

		void loadWeapons();
		void loadWeapon(const char* filename);
		fired::BaseWeapon *getWeapon(const char* name);

		void loadBodyparts();
		void loadBodypartsInDir(const char *dir, fired::BodypartType type);
		void loadBodypart(const char *dir, const char* filename, fired::BodypartType type);
		fired::BaseBodypart *getBodypart(const char* name, fired::BodypartType type);
	};
}

#endif
