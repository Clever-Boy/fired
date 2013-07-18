#ifndef __MOUSE
#define __MOUSE

#include <SFML/Graphics.hpp>

namespace fired {
	class Mouse {
		public:
		void ProcessEvent(sf::Event Event);
		void Draw();
		void Init();

		private:
		sf::Vector2f Pos;
	};
}

#endif
