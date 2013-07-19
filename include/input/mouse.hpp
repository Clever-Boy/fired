#ifndef __MOUSE
#define __MOUSE

#include <SFML/Graphics.hpp>
#include "prototypes.hpp"

namespace fired {
	class Mouse {
	private:
		fired::Game *Game;
		sf::Vector2f Pos;

	public:
		void Init(fired::Game *game);
		void Update(float FrameClock);
		void Render();

		void ProcessEvent(sf::Event Event);
	};
}

#endif
