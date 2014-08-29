/***********************************************************************
     * File       : menu_window_video.hpp
     * Created    : Aug 26, 2014
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#ifndef __MENU_WINDOW_VIDEO
#define __MENU_WINDOW_VIDEO


#include "menu_window.hpp"


namespace fired {
	struct MenuItemWindowVideo : MenuItemWindow {
		fired::InputList     *modes;
		fired::InputCheckbox *fullscreen;
		fired::InputButton   *apply;


		 MenuItemWindowVideo();
		~MenuItemWindowVideo();

		void update();
		void render();
		bool click(sf::Vector2f pos);
	};
}

#endif
