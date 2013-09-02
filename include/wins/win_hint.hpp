#ifndef __WIN_HINT
#define __WIN_HINT


#include "win_base.hpp"


namespace fired {
	struct HintWindow {
		fired::Window *win;
		fired::World  *world;
		sf::Text      *text;


		 HintWindow(fired::World *_world);
		~HintWindow();

		void update(fired::InventoryItem *_item);
		void render(fired::InventoryItem *_item);
		void renderText(float x, float y, const char *caption, bool rightAligned);
	};
}

#endif
