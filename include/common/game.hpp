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
#include "gamescreen.hpp"
#include "wins.hpp"
#include "control.hpp"
#include "menu.hpp"
#include "settings.hpp"
#include "screen.hpp"
#include "world.hpp"
#include "misc.hpp"
#include "ai.hpp"
#include "sqlite.hpp"


namespace fired {
	enum GameState {
		gsNone,
		gsStartScr,
		gsMainMenu,
		gsCreditsScr,
		gsWorld
	};


	class Game {
	private:
		sf::Clock        *clock;
		sf::Font         *font;
		sf::Image        *icon;
		sf::Music        *musicTheme;

		long lastClock;
		bool running;
		bool focused;

		fired::GameState     gameState;
		fired::GameState     gameStateNew;

		fired::Handlers      *handlers; 
		fired::GameScreen    *gameScreen;

		fired::Keyboard *keyboard;
		fired::Mouse    *mouse;


	public:
		 Game();
		~Game();

		void update();

		sf::Font         *getFont()     { return font; };
		bool              isRunning()   { return running; };
		void              stop()        { running = false; };

		void generateWorld();
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

#endif
