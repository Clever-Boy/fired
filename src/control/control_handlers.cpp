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
     * buttonStartBuilding

***********************************************************************/
void fired::Handlers::buttonStartBuilding() {
	game->generateWorld("Building");
	game->setGameState(gsWorld);
}



/***********************************************************************
     * Handlers
     * buttonStartMine

***********************************************************************/
void fired::Handlers::buttonStartMine() {
	game->generateWorld("Mine");
	game->setGameState(gsWorld);
}



/***********************************************************************
     * Handlers
     * buttonStartGraveyard

***********************************************************************/
void fired::Handlers::buttonStartGraveyard() {
	game->generateWorld("Graveyard");
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
