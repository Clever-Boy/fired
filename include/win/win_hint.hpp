/***********************************************************************
     * File       : win_hint.hpp
     * Created    : Sep 01, 2013
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#ifndef __WIN_HINT
#define __WIN_HINT


#include "win_base.hpp"


namespace fired {
	struct HintWindow {
		fired::Window *win;
		fired::World  *world;


		 HintWindow(fired::World *_world);
		~HintWindow();

		void update(fired::BaseItem *_item);
		void render(fired::BaseItem *_item);
	};
}

#endif
