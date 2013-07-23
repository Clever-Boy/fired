#ifndef __GAME
#define __GAME

#include <SFML/Graphics.hpp>
#include "prototypes.hpp"
#include "menu.hpp"
#include "input.hpp"
#include "settings.hpp"
#include "screen.hpp"


namespace fired {
	enum GameState {
		gsStartScr,
		gsMainMenu,
		gsCreditsScr
	};

	class Game {
		friend class fired::MainMenu;
		friend class fired::MenuItem;
		friend class fired::Mouse;
		friend class fired::Keyboard;
		friend class fired::Handlers;
		friend class fired::StartScr;
		friend class fired::CreditsScr;

	private:
		sf::RenderWindow app;
		sf::Clock clock;
		sf::Font font;

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

		fired::Keyboard keyboard;
		fired::Mouse mouse;

	public:
		void init();
		void update();

		bool isRunning() { return running; };
		void setGameState(fired::GameState state);
		void switchGameState();

		void processEvents();
		void processEvent(sf::Event event);
	};
}

#endif
