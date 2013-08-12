#ifndef __MOUSE
#define __MOUSE


#include <SFML/Graphics.hpp>
#include "prototypes.hpp"


namespace fired {
	class Mouse {
	private:
		sf::Vector2f pos;
		sf::Texture *mouseTex;
		sf::Sprite  *mouseCur;


	public:
		 Mouse();
		~Mouse();

		void update();
		void render();
	};
}

#endif
