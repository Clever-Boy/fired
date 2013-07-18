#ifndef __GAME
#define __GAME

#include <SFML/Graphics.hpp>

namespace fired {
	class Game {
	private:
		bool Running;
		sf::RenderWindow App;


	public:
		int Init();
		int Update();

		bool IsRunning() { return Running; };

		int ProcessEvents();
		int ProcessEvent(sf::Event Event);
	};
}
#endif
