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
	fired::WorldProperties props;

	props.creaturesLimit = 7;
	props.crittersLimit  = 5;
	props.bossesLimit    = 2;

	props.creaturesRate  =  5.0f;
	props.crittersRate   =  2.0f;
	props.bossesRate     = 30.0f;


	game->generateWorld("City", props);
	game->setGameState(gsWorld);
}



/***********************************************************************
     * Handlers
     * buttonStartForest

***********************************************************************/
void fired::Handlers::buttonStartForest() {
	fired::WorldProperties props;

	props.creaturesLimit = 0;
	props.crittersLimit  = 50;
	props.bossesLimit    = 0;

	props.creaturesRate  = 0.0f;
	props.crittersRate   = 0.5f;
	props.bossesRate     = 0.0f;


	game->generateWorld("Forest", props);
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
