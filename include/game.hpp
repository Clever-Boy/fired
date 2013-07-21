#ifndef __GAME
#define __GAME

#include <SFML/Graphics.hpp>
#include "prototypes.hpp"
#include "menu.hpp"
#include "input.hpp"
#include "settings.hpp"

namespace fired {
	class Game {
		friend class fired::MainMenu;
		friend class fired::MenuItem;
		friend class fired::Mouse;
		friend class fired::Keyboard;

	private:
		sf::RenderWindow app;
		sf::Clock clock;

		long lastClock;
		float frameClock;
		bool running;

		fired::Settings settings;
		fired::MainMenu mainMenu;

		fired::Keyboard keyboard;
		fired::Mouse mouse;

	public:
		void init();
		void update();
		void click(sf::Vector2i pos);

		bool isRunning() { return running; };

		void processEvents();
		void processEvent(sf::Event event);
	};
}

#endif
