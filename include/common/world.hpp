#ifndef __WORLD
#define __WORLD


#include <SFML/Graphics.hpp>
#include "map.hpp"
#include "char.hpp"
#include "prototypes.hpp"
#include "particle.hpp"
#include "theworld.hpp"


namespace fired {
	class World {
	private:
		fired::Game      *game;
		fired::Settings  *settings;
		sf::RenderWindow *app;

		fired::Map    map;
		fired::Camera cam;
		fired::Player player;

		std::vector<fired::ParticleSystem*> particles;
		std::vector<fired::Shot*>           shots;
		std::vector<fired::BaseWeapon*>     weapons;


	public:
		void init(fired::Game *_game);
		void deinit();
		void update();

		void processEvent(sf::Event event);
		void checkControls();

		void addShot(sf::Vector2f pos, float angle, float speed, fired::Character *owner);
		void addBulletSplash(sf::Vector2f pos, sf::Vector2f direction);

		fired::BaseWeapon *getWeapon(int index) {return weapons[index]; };
	};
}

#endif
