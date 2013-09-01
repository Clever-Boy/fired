#ifndef __WIN_HINT
#define __WIN_HINT


#include "win_base.hpp"


namespace fired {
	struct HintWindow {
		fired::Window *win;
		sf::Text      *text;


		 HintWindow();
		~HintWindow();

		void update();
		void render();
		void renderText(float x, float y, const char *caption, bool rightAligned);
	};
}

#endif
