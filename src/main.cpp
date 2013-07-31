#include "game.hpp"


float frameClock;
int main() {
	fired::Game Game;
	srand(time(NULL));

	Game.init();
	while(Game.isRunning()) Game.update();
	Game.deinit();

	return EXIT_SUCCESS;
}
