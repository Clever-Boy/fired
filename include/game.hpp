#ifndef __GAME
#define __GAME


#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>


#include "prototypes.hpp"
#include "menu.hpp"
#include "input.hpp"
#include "settings.hpp"
#include "screen.hpp"
#include "char.hpp"
#include "world.hpp"


namespace fired {
	enum GameState {
		gsNone,
		gsStartScr,
		gsMainMenu,
		gsCreditsScr,
		gsWorld
	};


	class Game {
		friend class fired::Handlers;


	private:
		sf::RenderWindow app;
		sf::Clock        clock;
		sf::Font         font;
		sf::Music        musicTheme;

		long lastClock;
		float frameClock;
		bool running;

		fired::GameState  gameState;
		fired::GameState  gameStateNew;
		fired::Settings   settings;
		fired::Handlers   handlers; 

		fired::MainMenu   mainMenu;
		fired::StartScr   startScr;
		fired::CreditsScr creditsScr;
		fired::World      world;

		fired::Keyboard keyboard;
		fired::Mouse mouse;


	public:
		void init();
		void deinit();
		void update();

		sf::RenderWindow *getApp()      { return &app; };
		sf::Font         *getFont()     { return &font; };
		fired::Settings  *getSettings() { return &settings; };
		bool              isRunning()   { return running; };

		void setGameState(fired::GameState state);
		void setMusic(const char *musicFile);
		void switchGameState();

		void processHandler(fired::Handler handler);
		void processEvents();
		void processEvent(sf::Event event);
	};
}

#endif
