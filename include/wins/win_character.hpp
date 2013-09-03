#ifndef __WIN_CHARACTER
#define __WIN_CHARACTER


#include "win_base.hpp"


namespace fired {
	struct CharacterWindow {
		fired::Window              *win;
		fired::Character           *owner;

		sf::Text *text;


		 CharacterWindow(fired::Character *_owner);
		~CharacterWindow();

		void update();
		void render();
		void renderText(float x, float y, const char *caption, bool rightAligned);
	};
}

#endif
