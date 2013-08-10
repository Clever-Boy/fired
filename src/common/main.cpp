#include "game.hpp"


float frameClock;
int main() {
	fired::Game *game = new fired::Game;
	srand(time(NULL));

	while(game->isRunning()) game->update();
	delete game;

	return EXIT_SUCCESS;
}
