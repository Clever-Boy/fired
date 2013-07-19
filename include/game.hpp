#ifndef __GAME
#define __GAME

#include <SFML/Graphics.hpp>
#include "prototypes.hpp"
#include "menu.hpp"
#include "input.hpp"

namespace fired {
	class Game {
		friend class fired::MainMenu;
		friend class fired::MenuItem;
		friend class fired::Mouse;
		friend class fired::Keyboard;

	private:
		sf::RenderWindow app;
		sf::Clock clock;

		float lastClock;
		float frameClock;
		bool running;

		fired::MainMenu mainMenu;

		fired::Keyboard keyboard;
		fired::Mouse mouse;

	public:
		void init();
		void update();

		bool isRunning() { return running; };

		void processEvents();
		void processEvent(sf::Event event);
	};
}

#endif
