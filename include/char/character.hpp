#ifndef __CHARACTER
#define __CHARACTER

#include <SFML/Graphics.hpp>
#include "prototypes.hpp"
#include "stats.hpp"


namespace fired {
	class Character {
	private:
		fired::Game      *game;
		fired::Settings  *settings;
		sf::RenderWindow *app;

		fired::CharacterStats baseStats;

		sf::Sprite   *sprite;
		sf::Texture  *texture;

		sf::Vector2f  pos;
		sf::Vector2f  velocity;
		sf::Vector2f  acceleration;

		sf::Vector2f  size;


	public:
		void init(fired::Game *_game);
		void deinit();
		void update();
		void render();

		void moveLeft();
		void moveRight();
	};
}

#endif
