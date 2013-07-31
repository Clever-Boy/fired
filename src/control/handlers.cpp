#include "game.hpp"

//======================================================================


void fired::Handlers::init(fired::Game *_game) {
	game = _game;
}

//======================================================================


void fired::Handlers::buttonStart() {
	game->generateWorld();
	game->setGameState(gsWorld);
}

//======================================================================


void fired::Handlers::buttonCredits() {
	game->setGameState(gsCreditsScr);
}

//======================================================================


void fired::Handlers::buttonExit() {
	game->stop();
}
