#ifndef __GAME
#define __GAME

#include <SFML/Graphics.hpp>
#include "prototypes.hpp"
#include "menu.hpp"
#include "input.hpp"

namespace fired {
	class Game {
		friend class fired::MainMenu;
		friend class fired::Mouse;
		friend class fired::Keyboard;

	private:
		sf::RenderWindow App;
		sf::Clock Clock;

		float LastClock;
		float FrameClock;
		bool Running;

		fired::MainMenu MainMenu;

		fired::Keyboard Keyboard;
		fired::Mouse Mouse;

	public:
		void Init();
		void Update();

		bool IsRunning() { return Running; };

		void ProcessEvents();
		void ProcessEvent(sf::Event Event);
	};
}

#endif
