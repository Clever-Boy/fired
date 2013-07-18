#ifndef __KEYBOARD
#define __KEYBOARD

#include <SFML/Graphics.hpp>

namespace fired {
	class Keyboard {
		public:
		void ProcessEvent(sf::Event Event);
		void Init();
	};
}

#endif
