#ifndef __CHARACTER
#define __CHARACTER


#include <SFML/Graphics.hpp>
#include "prototypes.hpp"
#include "stats.hpp"
#include "phys.hpp"
#include "model.hpp"


namespace fired {
	class Character {
		friend class Model;


	private:
		fired::Game      *game;
		fired::Settings  *settings;
		sf::RenderWindow *app;

		fired::CharacterStats baseStats;
		fired::Model          model;
		int  direction;
		int  watching;


	public:
		fired::Phys phys;
		fired::CharacterStats *getStats() { return &baseStats; };


		void init(fired::Game *_game);
		void deinit();
		void update();
		void render();


		void move();
		void moveLeft();
		void moveRight();
		void jump();

		void setWatching(int _watching) { watching = _watching; };
	};
}

#endif
