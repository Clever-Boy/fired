#include "game.hpp"


float             frameClock;
fired::Settings  *settings;
sf::RenderWindow *app;
fired::Game      *game;
fired::Container *container;


int main() {
	game = new fired::Game;
	srand(time(NULL));

	while(game->running) game->update();
	delete game;

	return EXIT_SUCCESS;
}
