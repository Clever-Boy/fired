/***********************************************************************
     * File       : control_handlers.cpp
     * Created    : Jul 26, 2013
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#include "game.hpp"



/***********************************************************************
     * Handlers
     * buttonStartCity

***********************************************************************/
void fired::Handlers::buttonStartCity() {
	game->generateWorld("City");
	game->setGameState(gsWorld);
}



/***********************************************************************
     * Handlers
     * buttonStartForest

***********************************************************************/
void fired::Handlers::buttonStartForest() {
	game->generateWorld("Forest");
	game->setGameState(gsWorld);
}



/***********************************************************************
     * Handlers
     * buttonCredits

***********************************************************************/
void fired::Handlers::buttonCredits() {
	game->setGameState(gsCreditsScr);
}



/***********************************************************************
     * Handlers
     * buttonExit

***********************************************************************/
void fired::Handlers::buttonExit() {
	game->stop();
}
