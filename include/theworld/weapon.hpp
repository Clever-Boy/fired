#ifndef __WEAPON
#define __WEAPON


#include <SFML/Graphics.hpp>
#include "prototypes.hpp"


namespace fired {
	class BaseWeapon {
		friend class Weapon;


	private:
		fired::Game      *game;
		fired::Settings  *settings;
		fired::Character *owner;
		fired::World     *world;
		sf::RenderWindow *app;

		sf::Texture *tex;
		sf::Sprite  *spr;


	public:
		void init(fired::Game *_game, fired::Character *_owner, fired::World *_world);
		void deinit();
		void update();
		void render();
	};


	class Weapon {
	private:
		fired::BaseWeapon *baseWeapon;


	public:
		void init(fired::BaseWeapon *_weapon);
		void deinit();
		void update();
		void render();
	};
}

#endif
