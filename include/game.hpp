#ifndef __GAME
#define __GAME

#include <SFML/Graphics.hpp>
#include "menu.hpp"
#include "input.hpp"

namespace fired {
	class Game {
	private:
		bool Running;
		sf::RenderWindow App;

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
