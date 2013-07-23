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
		friend class fired::StartScr;
		friend class fired::CreditsScr;

	private:
		sf::RenderWindow app;
		sf::Clock clock;
		sf::Font font;

		long lastClock;
		float frameClock;
		bool running;

		fired::GameState gameState;
		fired::Settings   settings;

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

		void processEvents();
		void processEvent(sf::Event event);
	};
}

#endif
