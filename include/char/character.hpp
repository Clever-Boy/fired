#ifndef __CHARACTER
#define __CHARACTER

#include <SFML/Graphics.hpp>
#include "prototypes.hpp"
#include "stats.hpp"
#include "phys.hpp"


namespace fired {
	class Character {
	private:
		fired::Game      *game;
		fired::Settings  *settings;
		sf::RenderWindow *app;

		fired::CharacterStats baseStats;
		int  direction;
		bool isMoving;

		sf::Sprite   *sprite;
		sf::Texture  *texture;


	public:
		fired::Phys phys;
		fired::CharacterStats *getStats() { return &baseStats; };

		void init(fired::Game *_game);
		void deinit();
		void update();
		void render();


		void moveLeft();
		void moveRight();
		void jump();
	};
}

#endif
