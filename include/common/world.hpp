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

		fired::Map       map;
		fired::Camera    cam;
		fired::Player    player;
		fired::GUI       gui;
		fired::Container container;

		std::vector<fired::ParticleSystem*> particles;
		std::vector<fired::Shot*>           shots;
		std::vector<fired::Creature*>       creatures;
		std::vector<fired::FlyText*>        texts;


	public:
		void init(fired::Game *_game);
		void deinit();
		void update();

		void processEvent(sf::Event event);
		void checkControls();
		void checkShots();
		void checkPhys(fired::Character *character) {map.checkPhys(character); };

		void addShot(sf::Vector2f pos, float angle, float speed, fired::Character *owner);
		void addText(sf::Vector2f pos, sf::Color color, int size, const char *text);
		void addBulletSplash(sf::Vector2f pos, sf::Vector2f direction);
		void addBloodSplash(sf::Vector2f pos, sf::Vector2f direction);

		fired::BaseWeapon *getWeapon(const char *name) {return container.getWeapon(name); };
	};
}

#endif
