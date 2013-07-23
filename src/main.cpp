#include "game.hpp"

int main() {
	fired::Game Game;

	Game.init();
	while(Game.isRunning()) Game.update();
	Game.deinit();

	return EXIT_SUCCESS;
}
