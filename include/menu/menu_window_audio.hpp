/***********************************************************************
     * File       : menu_window_audio.hpp
     * Created    : Aug 26, 2014
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#ifndef __MENU_WINDOW_AUDIO
#define __MENU_WINDOW_AUDIO


#include "menu_window.hpp"


namespace fired {
	struct MenuItemWindowAudio : MenuItemWindow {
		fired::InputScroller *musicVolume;
		fired::InputScroller *soundVolume;


		 MenuItemWindowAudio();
		~MenuItemWindowAudio();

		void update();
		void render();
		bool click(sf::Vector2f);
		void applyVideoSettings();
	};
}

#endif
