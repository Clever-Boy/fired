/***********************************************************************
     * File       : settings.hpp
     * Created    : Aug 02, 2013
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#ifndef __SETTINGS
#define __SETTINGS


namespace fired {
	struct Settings {
		struct {
			unsigned int width;
			unsigned int height;
			int bpp;
			bool fullScreen;
		} window;

		struct {
			int music;
			int sound;
		} volume;


		 Settings();
		~Settings();

		void save();
		void loadFromFile(const char *filename);
		void saveToFile(const char *filename);
	};
}

#endif
