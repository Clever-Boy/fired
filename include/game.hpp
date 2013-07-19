#ifndef __GAME
#define __GAME

#include <SFML/Graphics.hpp>
#include "prototypes.hpp"
#include "menu.hpp"
#include "input.hpp"

namespace fired {
	class Game {
	private:
		bool Running;

		fired::MainMenu MainMenu;

		fired::Keyboard Keyboard;
		fired::Mouse Mouse;

	public:
		sf::RenderWindow App;

		void Init();
		void Update();

		bool IsRunning() { return Running; };

		void ProcessEvents();
		void ProcessEvent(sf::Event Event);
	};
}

#endif
