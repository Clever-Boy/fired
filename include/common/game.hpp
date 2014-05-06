/***********************************************************************
     * File       : game.hpp
     * Created    : Aug 02, 2013
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#ifndef __GAME
#define __GAME


#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <sys/stat.h>
#include <stdio.h>
#include <dirent.h>
#include <fstream>
#include <string>
#include <string.h>
#include <math.h>


#include "defines.hpp"
#include "control.hpp"
#include "screen.hpp"
#include "menu.hpp"
#include "settings.hpp"
#include "resources.hpp"
#include "world.hpp"
#include "container.hpp"
#include "misc.hpp"
#include "mechanics.hpp"
#include "vect.hpp"
#include "ai.hpp"
#include "sqlite.hpp"


namespace fired {
	enum GameState {
		gsNone,
		gsLoadingScr,
		gsStartScr,
		gsMainMenu,
		gsCreditsScr,
		gsWorld
	};


	struct Game {
		sf::Clock        *clock;
		sf::Image        *icon;
		sf::Music        *musicTheme;

		long lastClock;
		bool running;
		bool focused;

		fired::GameState     gameState;
		fired::GameState     gameStateNew;

		fired::Mouse         *mouse;
		fired::Handlers      *handlers; 
		fired::GameScreen    *gameScreen;


		 Game();
		~Game();

		void update();
		void stop() { running = false; };

		void generateWorld(const char *biome);
		void setGameState(fired::GameState state);
		void setMusic(const char *musicFile);
		bool switchGameState();

		void processHandler(fired::Handler handler);
		void processEvents();
		void processEvent(sf::Event event);
	};
}


extern float                frameClock;
extern fired::Settings     *settings;
extern sf::RenderWindow    *app;
extern fired::Game         *game;
extern fired::Container    *container;
extern fired::Resources    *resources;

#endif
