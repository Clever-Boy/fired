#ifndef __GAME
#define __GAME


#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>


#include "prototypes.hpp"
#include "menu.hpp"
#include "input.hpp"
#include "settings.hpp"
#include "screen.hpp"
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
		friend class fired::MainMenu;
		friend class fired::MenuItem;
		friend class fired::Mouse;
		friend class fired::World;
		friend class fired::Keyboard;
		friend class fired::Handlers;
		friend class fired::StartScr;
		friend class fired::CreditsScr;


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

		sf::RenderWindow *getApp() { return &app; };
		fired::Settings *getSettings() { return &settings; };
		bool isRunning() { return running; };

		void setGameState(fired::GameState state);
		void switchGameState();

		void processEvents();
		void processEvent(sf::Event event);
	};
}

#endif
