/***********************************************************************
     * File       : main.cpp
     * Created    : Aug 02, 2013
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#include "game.hpp"



/***********************************************************************
     * Global variables

***********************************************************************/
float             frameClock;
fired::Settings  *settings;
sf::RenderWindow *app;
fired::Game      *game;
fired::Container *container;
fired::Resources *resources;



/***********************************************************************
     * Main function

***********************************************************************/
int main() {
	game = new fired::Game;
	srand(time(NULL));

	while(game->running) game->update();
	delete game;

	return EXIT_SUCCESS;
}
