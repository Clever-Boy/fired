#include "game.hpp"


float frameClock;
int main() {
	fired::Game Game;

	Game.init();
	while(Game.isRunning()) Game.update();
	Game.deinit();

	return EXIT_SUCCESS;
}
