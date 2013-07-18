#include "game.hpp"

int main() {
	fired::Game Game;

	Game.Init();
	while(Game.IsRunning()) Game.Update();

	return EXIT_SUCCESS;
}
