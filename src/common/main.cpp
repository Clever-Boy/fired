#include "game.hpp"


float             frameClock;
fired::Settings  *settings;
sf::RenderWindow *app;
fired::Game      *game;


int main() {
	game = new fired::Game;
	srand(time(NULL));

	while(game->isRunning()) game->update();
	delete game;

	return EXIT_SUCCESS;
}
