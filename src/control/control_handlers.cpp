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
     * buttonStart

***********************************************************************/
void fired::Handlers::buttonStart() {
	game->generateWorld();
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
